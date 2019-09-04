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
struct m_can_priv {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_OPEN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int m_can_clk_start (struct m_can_priv*) ; 
 int /*<<< orphan*/  m_can_clk_stop (struct m_can_priv*) ; 
 int /*<<< orphan*/  m_can_isr ; 
 int /*<<< orphan*/  m_can_start (struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct m_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int m_can_open(struct net_device *dev)
{
	struct m_can_priv *priv = netdev_priv(dev);
	int err;

	err = m_can_clk_start(priv);
	if (err)
		return err;

	/* open the can device */
	err = open_candev(dev);
	if (err) {
		netdev_err(dev, "failed to open can device\n");
		goto exit_disable_clks;
	}

	/* register interrupt handler */
	err = request_irq(dev->irq, m_can_isr, IRQF_SHARED, dev->name,
			  dev);
	if (err < 0) {
		netdev_err(dev, "failed to request interrupt\n");
		goto exit_irq_fail;
	}

	/* start the m_can controller */
	m_can_start(dev);

	can_led_event(dev, CAN_LED_EVENT_OPEN);
	napi_enable(&priv->napi);
	netif_start_queue(dev);

	return 0;

exit_irq_fail:
	close_candev(dev);
exit_disable_clks:
	m_can_clk_stop(priv);
	return err;
}