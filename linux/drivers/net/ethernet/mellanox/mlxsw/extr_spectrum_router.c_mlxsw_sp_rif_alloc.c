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
typedef  void* u16 ;
struct net_device {int /*<<< orphan*/  mtu; int /*<<< orphan*/  dev_addr; } ;
struct mlxsw_sp_rif {void* rif_index; void* vr_id; struct net_device* dev; int /*<<< orphan*/  mtu; int /*<<< orphan*/  addr; int /*<<< orphan*/  neigh_list; int /*<<< orphan*/  nexthop_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_rif* kzalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_rif *mlxsw_sp_rif_alloc(size_t rif_size, u16 rif_index,
					       u16 vr_id,
					       struct net_device *l3_dev)
{
	struct mlxsw_sp_rif *rif;

	rif = kzalloc(rif_size, GFP_KERNEL);
	if (!rif)
		return NULL;

	INIT_LIST_HEAD(&rif->nexthop_list);
	INIT_LIST_HEAD(&rif->neigh_list);
	if (l3_dev) {
		ether_addr_copy(rif->addr, l3_dev->dev_addr);
		rif->mtu = l3_dev->mtu;
		rif->dev = l3_dev;
	}
	rif->vr_id = vr_id;
	rif->rif_index = rif_index;

	return rif;
}