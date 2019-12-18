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
struct rcar_can_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  can_clk; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_STOP ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct rcar_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  rcar_can_stop (struct net_device*) ; 

__attribute__((used)) static int rcar_can_close(struct net_device *ndev)
{
	struct rcar_can_priv *priv = netdev_priv(ndev);

	netif_stop_queue(ndev);
	rcar_can_stop(ndev);
	free_irq(ndev->irq, ndev);
	napi_disable(&priv->napi);
	clk_disable_unprepare(priv->can_clk);
	clk_disable_unprepare(priv->clk);
	close_candev(ndev);
	can_led_event(ndev, CAN_LED_EVENT_STOP);
	return 0;
}