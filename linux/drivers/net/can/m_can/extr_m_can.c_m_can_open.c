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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct m_can_classdev {int /*<<< orphan*/  tx_wq; scalar_t__ is_peripheral; int /*<<< orphan*/  napi; int /*<<< orphan*/  tx_work; int /*<<< orphan*/ * tx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_OPEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int IRQF_TRIGGER_FALLING ; 
 int WQ_FREEZABLE ; 
 int WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int m_can_clk_start (struct m_can_classdev*) ; 
 int /*<<< orphan*/  m_can_clk_stop (struct m_can_classdev*) ; 
 int /*<<< orphan*/  m_can_isr ; 
 int /*<<< orphan*/  m_can_start (struct net_device*) ; 
 int /*<<< orphan*/  m_can_tx_work_queue ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct m_can_classdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int m_can_open(struct net_device *dev)
{
	struct m_can_classdev *cdev = netdev_priv(dev);
	int err;

	err = m_can_clk_start(cdev);
	if (err)
		return err;

	/* open the can device */
	err = open_candev(dev);
	if (err) {
		netdev_err(dev, "failed to open can device\n");
		goto exit_disable_clks;
	}

	/* register interrupt handler */
	if (cdev->is_peripheral) {
		cdev->tx_skb = NULL;
		cdev->tx_wq = alloc_workqueue("mcan_wq",
					      WQ_FREEZABLE | WQ_MEM_RECLAIM, 0);
		if (!cdev->tx_wq) {
			err = -ENOMEM;
			goto out_wq_fail;
		}

		INIT_WORK(&cdev->tx_work, m_can_tx_work_queue);

		err = request_threaded_irq(dev->irq, NULL, m_can_isr,
					   IRQF_ONESHOT | IRQF_TRIGGER_FALLING,
					   dev->name, dev);
	} else {
		err = request_irq(dev->irq, m_can_isr, IRQF_SHARED, dev->name,
				  dev);
	}

	if (err < 0) {
		netdev_err(dev, "failed to request interrupt\n");
		goto exit_irq_fail;
	}

	/* start the m_can controller */
	m_can_start(dev);

	can_led_event(dev, CAN_LED_EVENT_OPEN);

	if (!cdev->is_peripheral)
		napi_enable(&cdev->napi);

	netif_start_queue(dev);

	return 0;

exit_irq_fail:
	if (cdev->is_peripheral)
		destroy_workqueue(cdev->tx_wq);
out_wq_fail:
	close_candev(dev);
exit_disable_clks:
	m_can_clk_stop(cdev);
	return err;
}