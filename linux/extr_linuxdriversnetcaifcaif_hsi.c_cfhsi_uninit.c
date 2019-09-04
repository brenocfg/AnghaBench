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
struct cfhsi {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  cfhsi_get_device ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct cfhsi* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  symbol_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfhsi_uninit(struct net_device *dev)
{
	struct cfhsi *cfhsi = netdev_priv(dev);
	ASSERT_RTNL();
	symbol_put(cfhsi_get_device);
	list_del(&cfhsi->list);
}