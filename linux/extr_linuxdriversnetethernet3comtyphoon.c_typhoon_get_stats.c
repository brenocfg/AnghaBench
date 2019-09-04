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
struct net_device_stats {int dummy; } ;
struct typhoon {scalar_t__ card_state; struct net_device_stats stats_saved; TYPE_1__* dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device_stats stats; } ;

/* Variables and functions */
 scalar_t__ Sleeping ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct typhoon* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ typhoon_do_get_stats (struct typhoon*) ; 

__attribute__((used)) static struct net_device_stats *
typhoon_get_stats(struct net_device *dev)
{
	struct typhoon *tp = netdev_priv(dev);
	struct net_device_stats *stats = &tp->dev->stats;
	struct net_device_stats *saved = &tp->stats_saved;

	smp_rmb();
	if(tp->card_state == Sleeping)
		return saved;

	if(typhoon_do_get_stats(tp) < 0) {
		netdev_err(dev, "error getting stats\n");
		return saved;
	}

	return stats;
}