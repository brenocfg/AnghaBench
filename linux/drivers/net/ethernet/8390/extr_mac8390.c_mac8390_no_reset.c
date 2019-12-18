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
struct net_device {int dummy; } ;
struct ei_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ txing; } ;

/* Variables and functions */
 TYPE_1__ ei_status ; 
 int /*<<< orphan*/  hw ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct ei_device*,int /*<<< orphan*/ ,struct net_device*,char*) ; 

__attribute__((used)) static void mac8390_no_reset(struct net_device *dev)
{
	struct ei_device *ei_local = netdev_priv(dev);

	ei_status.txing = 0;
	netif_info(ei_local, hw, dev, "reset not supported\n");
}