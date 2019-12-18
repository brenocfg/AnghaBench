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
struct TYPE_2__ {int /*<<< orphan*/  vni; } ;
struct vxlan_dev {TYPE_1__ cfg; int /*<<< orphan*/  gro_cells; } ;
struct net_device {int /*<<< orphan*/  tstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gro_cells_destroy (int /*<<< orphan*/ *) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vxlan_fdb_delete_default (struct vxlan_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vxlan_uninit(struct net_device *dev)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);

	gro_cells_destroy(&vxlan->gro_cells);

	vxlan_fdb_delete_default(vxlan, vxlan->cfg.vni);

	free_percpu(dev->tstats);
}