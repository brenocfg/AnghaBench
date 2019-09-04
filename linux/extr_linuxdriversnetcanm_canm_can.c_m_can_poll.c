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
struct napi_struct {struct net_device* dev; } ;
struct m_can_priv {int irqstatus; } ;

/* Variables and functions */
 int IR_ERR_BUS_30X ; 
 int IR_ERR_STATE ; 
 int IR_RF0N ; 
 int /*<<< orphan*/  M_CAN_IR ; 
 int /*<<< orphan*/  M_CAN_PSR ; 
 scalar_t__ m_can_do_rx_poll (struct net_device*,int) ; 
 int /*<<< orphan*/  m_can_enable_all_interrupts (struct m_can_priv*) ; 
 scalar_t__ m_can_handle_bus_errors (struct net_device*,int,int) ; 
 scalar_t__ m_can_handle_state_errors (struct net_device*,int) ; 
 int m_can_read (struct m_can_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_complete_done (struct napi_struct*,int) ; 
 struct m_can_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int m_can_poll(struct napi_struct *napi, int quota)
{
	struct net_device *dev = napi->dev;
	struct m_can_priv *priv = netdev_priv(dev);
	int work_done = 0;
	u32 irqstatus, psr;

	irqstatus = priv->irqstatus | m_can_read(priv, M_CAN_IR);
	if (!irqstatus)
		goto end;

	psr = m_can_read(priv, M_CAN_PSR);
	if (irqstatus & IR_ERR_STATE)
		work_done += m_can_handle_state_errors(dev, psr);

	if (irqstatus & IR_ERR_BUS_30X)
		work_done += m_can_handle_bus_errors(dev, irqstatus, psr);

	if (irqstatus & IR_RF0N)
		work_done += m_can_do_rx_poll(dev, (quota - work_done));

	if (work_done < quota) {
		napi_complete_done(napi, work_done);
		m_can_enable_all_interrupts(priv);
	}

end:
	return work_done;
}