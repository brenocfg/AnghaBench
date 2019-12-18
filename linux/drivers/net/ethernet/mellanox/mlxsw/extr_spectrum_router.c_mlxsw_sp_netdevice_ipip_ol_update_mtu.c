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
struct net_device {int /*<<< orphan*/  mtu; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;
struct mlxsw_sp_rif_ipip_lb {TYPE_1__ common; int /*<<< orphan*/  ul_rif_id; int /*<<< orphan*/  ul_vr_id; } ;
struct mlxsw_sp_ipip_entry {struct mlxsw_sp_rif_ipip_lb* ol_lb; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_ipip_entry* mlxsw_sp_ipip_entry_find_by_ol_dev (struct mlxsw_sp*,struct net_device*) ; 
 int mlxsw_sp_rif_ipip_lb_op (struct mlxsw_sp_rif_ipip_lb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mlxsw_sp_netdevice_ipip_ol_update_mtu(struct mlxsw_sp *mlxsw_sp,
						 struct net_device *ol_dev)
{
	struct mlxsw_sp_ipip_entry *ipip_entry;
	struct mlxsw_sp_rif_ipip_lb *lb_rif;
	int err = 0;

	ipip_entry = mlxsw_sp_ipip_entry_find_by_ol_dev(mlxsw_sp, ol_dev);
	if (ipip_entry) {
		lb_rif = ipip_entry->ol_lb;
		err = mlxsw_sp_rif_ipip_lb_op(lb_rif, lb_rif->ul_vr_id,
					      lb_rif->ul_rif_id, true);
		if (err)
			goto out;
		lb_rif->common.mtu = ol_dev->mtu;
	}

out:
	return err;
}