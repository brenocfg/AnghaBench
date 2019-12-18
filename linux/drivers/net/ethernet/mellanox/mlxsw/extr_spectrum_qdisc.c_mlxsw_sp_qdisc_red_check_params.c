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
struct tc_red_qopt_offload_params {scalar_t__ min; scalar_t__ max; } ;
struct mlxsw_sp_qdisc {int dummy; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {TYPE_1__* bus_info; int /*<<< orphan*/  core; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_BUFFER_SIZE ; 
 scalar_t__ MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
mlxsw_sp_qdisc_red_check_params(struct mlxsw_sp_port *mlxsw_sp_port,
				struct mlxsw_sp_qdisc *mlxsw_sp_qdisc,
				void *params)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	struct tc_red_qopt_offload_params *p = params;

	if (p->min > p->max) {
		dev_err(mlxsw_sp->bus_info->dev,
			"spectrum: RED: min %u is bigger then max %u\n", p->min,
			p->max);
		return -EINVAL;
	}
	if (p->max > MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_BUFFER_SIZE)) {
		dev_err(mlxsw_sp->bus_info->dev,
			"spectrum: RED: max value %u is too big\n", p->max);
		return -EINVAL;
	}
	if (p->min == 0 || p->max == 0) {
		dev_err(mlxsw_sp->bus_info->dev,
			"spectrum: RED: 0 value is illegal for min and max\n");
		return -EINVAL;
	}
	return 0;
}