#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device_stats {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {struct net_device_stats stats; } ;
struct m_can_classdev {int irqstatus; int version; int /*<<< orphan*/  napi; int /*<<< orphan*/  is_peripheral; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* clear_interrupts ) (struct m_can_classdev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_TX ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int IR_ALL_INT ; 
 int IR_ERR_ALL_30X ; 
 int IR_RF0N ; 
 int IR_TC ; 
 int IR_TEFN ; 
 int /*<<< orphan*/  M_CAN_IR ; 
 scalar_t__ can_get_echo_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_can_disable_all_interrupts (struct m_can_classdev*) ; 
 int /*<<< orphan*/  m_can_echo_tx_event (struct net_device*) ; 
 int m_can_read (struct m_can_classdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_can_rx_peripheral (struct net_device*) ; 
 int /*<<< orphan*/  m_can_tx_fifo_full (struct m_can_classdev*) ; 
 int /*<<< orphan*/  m_can_write (struct m_can_classdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct m_can_classdev* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct m_can_classdev*) ; 

__attribute__((used)) static irqreturn_t m_can_isr(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct m_can_classdev *cdev = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	u32 ir;

	ir = m_can_read(cdev, M_CAN_IR);
	if (!ir)
		return IRQ_NONE;

	/* ACK all irqs */
	if (ir & IR_ALL_INT)
		m_can_write(cdev, M_CAN_IR, ir);

	if (cdev->ops->clear_interrupts)
		cdev->ops->clear_interrupts(cdev);

	/* schedule NAPI in case of
	 * - rx IRQ
	 * - state change IRQ
	 * - bus error IRQ and bus error reporting
	 */
	if ((ir & IR_RF0N) || (ir & IR_ERR_ALL_30X)) {
		cdev->irqstatus = ir;
		m_can_disable_all_interrupts(cdev);
		if (!cdev->is_peripheral)
			napi_schedule(&cdev->napi);
		else
			m_can_rx_peripheral(dev);
	}

	if (cdev->version == 30) {
		if (ir & IR_TC) {
			/* Transmission Complete Interrupt*/
			stats->tx_bytes += can_get_echo_skb(dev, 0);
			stats->tx_packets++;
			can_led_event(dev, CAN_LED_EVENT_TX);
			netif_wake_queue(dev);
		}
	} else  {
		if (ir & IR_TEFN) {
			/* New TX FIFO Element arrived */
			m_can_echo_tx_event(dev);
			can_led_event(dev, CAN_LED_EVENT_TX);
			if (netif_queue_stopped(dev) &&
			    !m_can_tx_fifo_full(cdev))
				netif_wake_queue(dev);
		}
	}

	return IRQ_HANDLED;
}