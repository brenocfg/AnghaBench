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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct c_can_priv {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_OPEN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  c_can_irq_control (struct c_can_priv*,int) ; 
 int /*<<< orphan*/  c_can_isr ; 
 int /*<<< orphan*/  c_can_pm_runtime_get_sync (struct c_can_priv*) ; 
 int /*<<< orphan*/  c_can_pm_runtime_put_sync (struct c_can_priv*) ; 
 int /*<<< orphan*/  c_can_reset_ram (struct c_can_priv*,int) ; 
 int c_can_start (struct net_device*) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int c_can_open(struct net_device *dev)
{
	int err;
	struct c_can_priv *priv = netdev_priv(dev);

	c_can_pm_runtime_get_sync(priv);
	c_can_reset_ram(priv, true);

	/* open the can device */
	err = open_candev(dev);
	if (err) {
		netdev_err(dev, "failed to open can device\n");
		goto exit_open_fail;
	}

	/* register interrupt handler */
	err = request_irq(dev->irq, &c_can_isr, IRQF_SHARED, dev->name,
				dev);
	if (err < 0) {
		netdev_err(dev, "failed to request interrupt\n");
		goto exit_irq_fail;
	}

	/* start the c_can controller */
	err = c_can_start(dev);
	if (err)
		goto exit_start_fail;

	can_led_event(dev, CAN_LED_EVENT_OPEN);

	napi_enable(&priv->napi);
	/* enable status change, error and module interrupts */
	c_can_irq_control(priv, true);
	netif_start_queue(dev);

	return 0;

exit_start_fail:
	free_irq(dev->irq, dev);
exit_irq_fail:
	close_candev(dev);
exit_open_fail:
	c_can_reset_ram(priv, false);
	c_can_pm_runtime_put_sync(priv);
	return err;
}