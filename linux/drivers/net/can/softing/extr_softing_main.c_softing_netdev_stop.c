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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int softing_startstop (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int softing_netdev_stop(struct net_device *ndev)
{
	int ret;

	netif_stop_queue(ndev);

	/* softing cycle does close_candev() */
	ret = softing_startstop(ndev, 0);
	return ret;
}