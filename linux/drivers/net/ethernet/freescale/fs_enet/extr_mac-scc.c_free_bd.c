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
struct fs_enet_private {int /*<<< orphan*/  ring_mem_addr; scalar_t__ ring_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpm_dpfree (int /*<<< orphan*/ ) ; 
 struct fs_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void free_bd(struct net_device *dev)
{
	struct fs_enet_private *fep = netdev_priv(dev);

	if (fep->ring_base)
		cpm_dpfree(fep->ring_mem_addr);
}