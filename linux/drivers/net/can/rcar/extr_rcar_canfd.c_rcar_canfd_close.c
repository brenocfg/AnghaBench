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
struct rcar_canfd_global {int /*<<< orphan*/  can_clk; } ;
struct rcar_canfd_channel {int /*<<< orphan*/  napi; struct rcar_canfd_global* gpriv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_STOP ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct rcar_canfd_channel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  rcar_canfd_stop (struct net_device*) ; 

__attribute__((used)) static int rcar_canfd_close(struct net_device *ndev)
{
	struct rcar_canfd_channel *priv = netdev_priv(ndev);
	struct rcar_canfd_global *gpriv = priv->gpriv;

	netif_stop_queue(ndev);
	rcar_canfd_stop(ndev);
	napi_disable(&priv->napi);
	clk_disable_unprepare(gpriv->can_clk);
	close_candev(ndev);
	can_led_event(ndev, CAN_LED_EVENT_STOP);
	return 0;
}