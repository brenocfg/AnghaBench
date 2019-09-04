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
struct TYPE_2__ {scalar_t__ protocol; } ;
struct tc_cls_matchall_offload {int /*<<< orphan*/  exts; int /*<<< orphan*/  cookie; TYPE_1__ common; } ;
struct tc_action {int dummy; } ;
struct mlxsw_sp_port_mall_mirror_tc_entry {int dummy; } ;
struct mlxsw_sp_port_mall_tc_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  type; struct mlxsw_sp_port_mall_mirror_tc_entry mirror; int /*<<< orphan*/  cookie; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  mall_tc_list; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_ALL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_SP_PORT_MALL_MIRROR ; 
 int /*<<< orphan*/  MLXSW_SP_PORT_MALL_SAMPLE ; 
 int /*<<< orphan*/  actions ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ is_tcf_mirred_egress_mirror (struct tc_action const*) ; 
 scalar_t__ is_tcf_sample (struct tc_action const*) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_port_mall_tc_entry*) ; 
 struct mlxsw_sp_port_mall_tc_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_port_add_cls_matchall_mirror (struct mlxsw_sp_port*,struct mlxsw_sp_port_mall_mirror_tc_entry*,struct tc_action const*,int) ; 
 int mlxsw_sp_port_add_cls_matchall_sample (struct mlxsw_sp_port*,struct tc_cls_matchall_offload*,struct tc_action const*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct tc_action* tcf_exts_first_action (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_exts_has_one_action (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_port_add_cls_matchall(struct mlxsw_sp_port *mlxsw_sp_port,
					  struct tc_cls_matchall_offload *f,
					  bool ingress)
{
	struct mlxsw_sp_port_mall_tc_entry *mall_tc_entry;
	__be16 protocol = f->common.protocol;
	const struct tc_action *a;
	LIST_HEAD(actions);
	int err;

	if (!tcf_exts_has_one_action(f->exts)) {
		netdev_err(mlxsw_sp_port->dev, "only singular actions are supported\n");
		return -EOPNOTSUPP;
	}

	mall_tc_entry = kzalloc(sizeof(*mall_tc_entry), GFP_KERNEL);
	if (!mall_tc_entry)
		return -ENOMEM;
	mall_tc_entry->cookie = f->cookie;

	a = tcf_exts_first_action(f->exts);

	if (is_tcf_mirred_egress_mirror(a) && protocol == htons(ETH_P_ALL)) {
		struct mlxsw_sp_port_mall_mirror_tc_entry *mirror;

		mall_tc_entry->type = MLXSW_SP_PORT_MALL_MIRROR;
		mirror = &mall_tc_entry->mirror;
		err = mlxsw_sp_port_add_cls_matchall_mirror(mlxsw_sp_port,
							    mirror, a, ingress);
	} else if (is_tcf_sample(a) && protocol == htons(ETH_P_ALL)) {
		mall_tc_entry->type = MLXSW_SP_PORT_MALL_SAMPLE;
		err = mlxsw_sp_port_add_cls_matchall_sample(mlxsw_sp_port, f,
							    a, ingress);
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