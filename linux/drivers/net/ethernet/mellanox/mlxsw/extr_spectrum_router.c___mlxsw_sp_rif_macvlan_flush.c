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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct mlxsw_sp_rif {int /*<<< orphan*/  fid; int /*<<< orphan*/  mlxsw_sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_fid_index (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_rif_fdb_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_is_macvlan (struct net_device*) ; 

__attribute__((used)) static int __mlxsw_sp_rif_macvlan_flush(struct net_device *dev, void *data)
{
	struct mlxsw_sp_rif *rif = data;

	if (!netif_is_macvlan(dev))
		return 0;

	return mlxsw_sp_rif_fdb_op(rif->mlxsw_sp, dev->dev_addr,
				   mlxsw_sp_fid_index(rif->fid), false);
}