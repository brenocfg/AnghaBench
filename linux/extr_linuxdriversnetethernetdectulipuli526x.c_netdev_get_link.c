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
typedef  int u32 ;
struct uli526x_board_info {scalar_t__ link_failed; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct uli526x_board_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 netdev_get_link(struct net_device *dev) {
	struct uli526x_board_info *np = netdev_priv(dev);

	if(np->link_failed)
		return 0;
	else
		return 1;
}