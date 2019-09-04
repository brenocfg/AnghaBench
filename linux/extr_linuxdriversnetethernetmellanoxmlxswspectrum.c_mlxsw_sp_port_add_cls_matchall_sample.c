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
struct tc_cls_matchall_offload {int dummy; } ;
struct tc_action {int dummy; } ;
struct mlxsw_sp_port {TYPE_1__* sample; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  psample_group; scalar_t__ rate; int /*<<< orphan*/  trunc_size; int /*<<< orphan*/  truncate; } ;

/* Variables and functions */
 int EEXIST ; 
 int EOPNOTSUPP ; 
 scalar_t__ MLXSW_REG_MPSC_RATE_MAX ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_port_sample_set (struct mlxsw_sp_port*,int,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_sample_psample_group (struct tc_action const*) ; 
 scalar_t__ tcf_sample_rate (struct tc_action const*) ; 
 int /*<<< orphan*/  tcf_sample_trunc_size (struct tc_action const*) ; 
 int /*<<< orphan*/  tcf_sample_truncate (struct tc_action const*) ; 

__attribute__((used)) static int
mlxsw_sp_port_add_cls_matchall_sample(struct mlxsw_sp_port *mlxsw_sp_port,
				      struct tc_cls_matchall_offload *cls,
				      const struct tc_action *a,
				      bool ingress)
{
	int err;

	if (!mlxsw_sp_port->sample)
		return -EOPNOTSUPP;
	if (rtnl_dereference(mlxsw_sp_port->sample->psample_group)) {
		netdev_err(mlxsw_sp_port->dev, "sample already active\n");
		return -EEXIST;
	}
	if (tcf_sample_rate(a) > MLXSW_REG_MPSC_RATE_MAX) {
		netdev_err(mlxsw_sp_port->dev, "sample rate not supported\n");
		return -EOPNOTSUPP;
	}

	rcu_assign_pointer(mlxsw_sp_port->sample->psample_group,
			   tcf_sample_psample_group(a));
	mlxsw_sp_port->sample->truncate = tcf_sample_truncate(a);
	mlxsw_sp_port->sample->trunc_size = tcf_sample_trunc_size(a);
	mlxsw_sp_port->sample->rate = tcf_sample_rate(a);

	err = mlxsw_sp_port_sample_set(mlxsw_sp_port, true, tcf_sample_rate(a));
	if (err)
		goto err_port_sample_set;
	return 0;

err_port_sample_set:
	RCU_INIT_POINTER(mlxsw_sp_port->sample->psample_group, NULL);
	return err;
}