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
struct mlxsw_sp_port_mall_mirror_tc_entry {int ingress; int /*<<< orphan*/  span_id; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  dev; } ;
struct flow_action_entry {int /*<<< orphan*/  dev; } ;
typedef  enum mlxsw_sp_span_type { ____Placeholder_mlxsw_sp_span_type } mlxsw_sp_span_type ;

/* Variables and functions */
 int EINVAL ; 
 int MLXSW_SP_SPAN_EGRESS ; 
 int MLXSW_SP_SPAN_INGRESS ; 
 int mlxsw_sp_span_mirror_add (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
mlxsw_sp_port_add_cls_matchall_mirror(struct mlxsw_sp_port *mlxsw_sp_port,
				      struct mlxsw_sp_port_mall_mirror_tc_entry *mirror,
				      const struct flow_action_entry *act,
				      bool ingress)
{
	enum mlxsw_sp_span_type span_type;

	if (!act->dev) {
		netdev_err(mlxsw_sp_port->dev, "Could not find requested device\n");
		return -EINVAL;
	}

	mirror->ingress = ingress;
	span_type = ingress ? MLXSW_SP_SPAN_INGRESS : MLXSW_SP_SPAN_EGRESS;
	return mlxsw_sp_span_mirror_add(mlxsw_sp_port, act->dev, span_type,
					true, &mirror->span_id);
}