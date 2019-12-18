#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct m_can_classdev {int irqstatus; int version; } ;
struct can_berr_counter {int rxerr; } ;

/* Variables and functions */
 int ECR_RP ; 
 int IR_ERR_BUS_30X ; 
 int IR_ERR_STATE ; 
 int IR_MRAF ; 
 int IR_RF0N ; 
 int /*<<< orphan*/  M_CAN_ECR ; 
 int /*<<< orphan*/  M_CAN_IR ; 
 int /*<<< orphan*/  M_CAN_PSR ; 
 int /*<<< orphan*/  __m_can_get_berr_counter (struct net_device*,struct can_berr_counter*) ; 
 scalar_t__ m_can_do_rx_poll (struct net_device*,int) ; 
 scalar_t__ m_can_handle_bus_errors (struct net_device*,int,int) ; 
 scalar_t__ m_can_handle_state_errors (struct net_device*,int) ; 
 int m_can_read (struct m_can_classdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_can_write (struct m_can_classdev*,int /*<<< orphan*/ ,int) ; 
 struct m_can_classdev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int m_can_rx_handler(struct net_device *dev, int quota)
{
	struct m_can_classdev *cdev = netdev_priv(dev);
	int work_done = 0;
	u32 irqstatus, psr;

	irqstatus = cdev->irqstatus | m_can_read(cdev, M_CAN_IR);
	if (!irqstatus)
		goto end;

	/* Errata workaround for issue "Needless activation of MRAF irq"
	 * During frame reception while the MCAN is in Error Passive state
	 * and the Receive Error Counter has the value MCAN_ECR.REC = 127,
	 * it may happen that MCAN_IR.MRAF is set although there was no
	 * Message RAM access failure.
	 * If MCAN_IR.MRAF is enabled, an interrupt to the Host CPU is generated
	 * The Message RAM Access Failure interrupt routine needs to check
	 * whether MCAN_ECR.RP = ’1’ and MCAN_ECR.REC = 127.
	 * In this case, reset MCAN_IR.MRAF. No further action is required.
	 */
	if (cdev->version <= 31 && irqstatus & IR_MRAF &&
	    m_can_read(cdev, M_CAN_ECR) & ECR_RP) {
		struct can_berr_counter bec;

		__m_can_get_berr_counter(dev, &bec);
		if (bec.rxerr == 127) {
			m_can_write(cdev, M_CAN_IR, IR_MRAF);
			irqstatus &= ~IR_MRAF;
		}
	}

	psr = m_can_read(cdev, M_CAN_PSR);

	if (irqstatus & IR_ERR_STATE)
		work_done += m_can_handle_state_errors(dev, psr);

	if (irqstatus & IR_ERR_BUS_30X)
		work_done += m_can_handle_bus_errors(dev, irqstatus, psr);

	if (irqstatus & IR_RF0N)
		work_done += m_can_do_rx_poll(dev, (quota - work_done));
end:
	return work_done;
}