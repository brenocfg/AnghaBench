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
struct tg3 {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tg3_set_rx_mode (struct net_device*) ; 
 struct tg3* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  tg3_full_lock (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_full_unlock (struct tg3*) ; 

__attribute__((used)) static void tg3_set_rx_mode(struct net_device *dev)
{
	struct tg3 *tp = netdev_priv(dev);

	if (!netif_running(dev))
		return;

	tg3_full_lock(tp, 0);
	__tg3_set_rx_mode(dev);
	tg3_full_unlock(tp);
}