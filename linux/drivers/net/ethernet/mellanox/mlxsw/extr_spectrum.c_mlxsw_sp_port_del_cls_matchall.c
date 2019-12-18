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
struct tc_cls_matchall_offload {int /*<<< orphan*/  cookie; } ;
struct mlxsw_sp_port_mall_tc_entry {int type; int /*<<< orphan*/  mirror; int /*<<< orphan*/  list; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  MLXSW_SP_PORT_MALL_MIRROR 129 
#define  MLXSW_SP_PORT_MALL_SAMPLE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_port_mall_tc_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_port_del_cls_matchall_mirror (struct mlxsw_sp_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_port_del_cls_matchall_sample (struct mlxsw_sp_port*) ; 
 struct mlxsw_sp_port_mall_tc_entry* mlxsw_sp_port_mall_tc_entry_find (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mlxsw_sp_port_del_cls_matchall(struct mlxsw_sp_port *mlxsw_sp_port,
					   struct tc_cls_matchall_offload *f)
{
	struct mlxsw_sp_port_mall_tc_entry *mall_tc_entry;

	mall_tc_entry = mlxsw_sp_port_mall_tc_entry_find(mlxsw_sp_port,
							 f->cookie);
	if (!mall_tc_entry) {
		netdev_dbg(mlxsw_sp_port->dev, "tc entry not found on port\n");
		return;
	}
	list_del(&mall_tc_entry->list);

	switch (mall_tc_entry->type) {
	case MLXSW_SP_PORT_MALL_MIRROR:
		mlxsw_sp_port_del_cls_matchall_mirror(mlxsw_sp_port,
						      &mall_tc_entry->mirror);
		break;
	case MLXSW_SP_PORT_MALL_SAMPLE:
		mlxsw_sp_port_del_cls_matchall_sample(mlxsw_sp_port);
		break;
	default:
		WARN_ON(1);
	}

	kfree(mall_tc_entry);
}