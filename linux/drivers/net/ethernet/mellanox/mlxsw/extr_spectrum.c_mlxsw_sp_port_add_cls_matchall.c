#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ protocol; } ;
struct tc_cls_matchall_offload {TYPE_2__* rule; int /*<<< orphan*/  cookie; TYPE_1__ common; } ;
struct mlxsw_sp_port_mall_mirror_tc_entry {int dummy; } ;
struct mlxsw_sp_port_mall_tc_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  type; struct mlxsw_sp_port_mall_mirror_tc_entry mirror; int /*<<< orphan*/  cookie; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  mall_tc_list; int /*<<< orphan*/  dev; } ;
struct flow_action_entry {scalar_t__ id; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_6__ {struct flow_action_entry* entries; } ;
struct TYPE_5__ {TYPE_3__ action; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_ALL ; 
 scalar_t__ FLOW_ACTION_MIRRED ; 
 scalar_t__ FLOW_ACTION_SAMPLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLXSW_SP_PORT_MALL_MIRROR ; 
 int /*<<< orphan*/  MLXSW_SP_PORT_MALL_SAMPLE ; 
 int /*<<< orphan*/  flow_offload_has_one_action (TYPE_3__*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_port_mall_tc_entry*) ; 
 struct mlxsw_sp_port_mall_tc_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_port_add_cls_matchall_mirror (struct mlxsw_sp_port*,struct mlxsw_sp_port_mall_mirror_tc_entry*,struct flow_action_entry*,int) ; 
 int mlxsw_sp_port_add_cls_matchall_sample (struct mlxsw_sp_port*,struct tc_cls_matchall_offload*,struct flow_action_entry*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mlxsw_sp_port_add_cls_matchall(struct mlxsw_sp_port *mlxsw_sp_port,
					  struct tc_cls_matchall_offload *f,
					  bool ingress)
{
	struct mlxsw_sp_port_mall_tc_entry *mall_tc_entry;
	__be16 protocol = f->common.protocol;
	struct flow_action_entry *act;
	int err;

	if (!flow_offload_has_one_action(&f->rule->action)) {
		netdev_err(mlxsw_sp_port->dev, "only singular actions are supported\n");
		return -EOPNOTSUPP;
	}

	mall_tc_entry = kzalloc(sizeof(*mall_tc_entry), GFP_KERNEL);
	if (!mall_tc_entry)
		return -ENOMEM;
	mall_tc_entry->cookie = f->cookie;

	act = &f->rule->action.entries[0];

	if (act->id == FLOW_ACTION_MIRRED && protocol == htons(ETH_P_ALL)) {
		struct mlxsw_sp_port_mall_mirror_tc_entry *mirror;

		mall_tc_entry->type = MLXSW_SP_PORT_MALL_MIRROR;
		mirror = &mall_tc_entry->mirror;
		err = mlxsw_sp_port_add_cls_matchall_mirror(mlxsw_sp_port,
							    mirror, act,
							    ingress);
	} else if (act->id == FLOW_ACTION_SAMPLE &&
		   protocol == htons(ETH_P_ALL)) {
		mall_tc_entry->type = MLXSW_SP_PORT_MALL_SAMPLE;
		err = mlxsw_sp_port_add_cls_matchall_sample(mlxsw_sp_port, f,
							    act, ingress);
	} else {
		err = -EOPNOTSUPP;
	}

	if (err)
		goto err_add_action;

	list_add_tail(&mall_tc_entry->list, &mlxsw_sp_port->mall_tc_list);
	return 0;

err_add_action:
	kfree(mall_tc_entry);
	return err;
}