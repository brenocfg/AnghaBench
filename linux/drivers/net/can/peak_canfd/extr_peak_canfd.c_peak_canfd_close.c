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
struct peak_canfd_priv {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 struct peak_canfd_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  peak_canfd_stop (struct peak_canfd_priv*) ; 

__attribute__((used)) static int peak_canfd_close(struct net_device *ndev)
{
	struct peak_canfd_priv *priv = netdev_priv(ndev);

	netif_stop_queue(ndev);
	peak_canfd_stop(priv);
	close_candev(ndev);

	return 0;
}