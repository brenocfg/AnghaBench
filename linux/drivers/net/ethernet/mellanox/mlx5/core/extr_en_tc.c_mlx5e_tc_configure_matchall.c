#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  prio; struct netlink_ext_ack* extack; } ;
struct tc_cls_matchall_offload {TYPE_2__* rule; TYPE_1__ common; } ;
struct netlink_ext_ack {int dummy; } ;
struct mlx5e_priv {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int TC_H_MAJ (int /*<<< orphan*/ ) ; 
 int scan_tc_matchall_fdb_actions (struct mlx5e_priv*,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 

int mlx5e_tc_configure_matchall(struct mlx5e_priv *priv,
				struct tc_cls_matchall_offload *ma)
{
	struct netlink_ext_ack *extack = ma->common.extack;
	int prio = TC_H_MAJ(ma->common.prio) >> 16;

	if (prio != 1) {
		NL_SET_ERR_MSG_MOD(extack, "only priority 1 is supported");
		return -EINVAL;
	}

	return scan_tc_matchall_fdb_actions(priv, &ma->rule->action, extack);
}