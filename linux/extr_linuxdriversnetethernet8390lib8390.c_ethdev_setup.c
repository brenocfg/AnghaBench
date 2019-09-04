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
struct ei_device {int msg_enable; int /*<<< orphan*/  page_lock; } ;

/* Variables and functions */
 int NETIF_MSG_DRV ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int msg_enable ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  version ; 
 int /*<<< orphan*/  version_printed ; 

__attribute__((used)) static void ethdev_setup(struct net_device *dev)
{
	struct ei_device *ei_local = netdev_priv(dev);

	if ((msg_enable & NETIF_MSG_DRV) && (version_printed++ == 0))
		pr_info("%s", version);

	ether_setup(dev);

	spin_lock_init(&ei_local->page_lock);

	ei_local->msg_enable = msg_enable;
}