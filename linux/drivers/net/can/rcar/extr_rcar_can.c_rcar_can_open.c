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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_OPEN ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,...) ; 
 struct rcar_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int /*<<< orphan*/  rcar_can_interrupt ; 
 int /*<<< orphan*/  rcar_can_start (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int rcar_can_open(struct net_device *ndev)
{
	struct rcar_can_priv *priv = netdev_priv(ndev);
	int err;

	err = clk_prepare_enable(priv->clk);
	if (err) {
		netdev_err(ndev,
			   "failed to enable peripheral clock, error %d\n",
			   err);
		goto out;
	}
	err = clk_prepare_enable(priv->can_clk);
	if (err) {
		netdev_err(ndev, "failed to enable CAN clock, error %d\n",
			   err);
		goto out_clock;
	}
	err = open_candev(ndev);
	if (err) {
		netdev_err(ndev, "open_candev() failed, error %d\n", err);
		goto out_can_clock;
	}
	napi_enable(&priv->napi);
	err = request_irq(ndev->irq, rcar_can_interrupt, 0, ndev->name, ndev);
	if (err) {
		netdev_err(ndev, "request_irq(%d) failed, error %d\n",
			   ndev->irq, err);
		goto out_close;
	}
	can_led_event(ndev, CAN_LED_EVENT_OPEN);
	rcar_can_start(ndev);
	netif_start_queue(ndev);
	return 0;
out_close:
	napi_disable(&priv->napi);
	close_candev(ndev);
out_can_clock:
	clk_disable_unprepare(priv->can_clk);
out_clock:
	clk_disable_unprepare(priv->clk);
out:
	return err;
}