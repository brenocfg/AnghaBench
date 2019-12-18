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
struct TYPE_2__ {scalar_t__ htlo; scalar_t__ hthi; } ;
struct fs_enet_private {TYPE_1__ fec; } ;

/* Variables and functions */
 struct fs_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void set_multicast_start(struct net_device *dev)
{
	struct fs_enet_private *fep = netdev_priv(dev);

	fep->fec.hthi = 0;
	fep->fec.htlo = 0;
}