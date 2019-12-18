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
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_namespace {int dummy; } ;
struct TYPE_3__ {struct mlx5_flow_table* vepa_fdb; } ;
struct TYPE_4__ {TYPE_1__ legacy; } ;
struct mlx5_eswitch {TYPE_2__ fdb_table; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  LEGACY_VEPA_PRIO ; 
 int PTR_ERR (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  esw_warn (struct mlx5_core_dev*,char*,...) ; 
 struct mlx5_flow_table* mlx5_create_auto_grouped_flow_table (struct mlx5_flow_namespace*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_flow_namespace* mlx5_get_fdb_sub_ns (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esw_create_legacy_vepa_table(struct mlx5_eswitch *esw)
{
	struct mlx5_core_dev *dev = esw->dev;
	struct mlx5_flow_namespace *root_ns;
	struct mlx5_flow_table *fdb;
	int err;

	root_ns = mlx5_get_fdb_sub_ns(dev, 0);
	if (!root_ns) {
		esw_warn(dev, "Failed to get FDB flow namespace\n");
		return -EOPNOTSUPP;
	}

	/* num FTE 2, num FG 2 */
	fdb = mlx5_create_auto_grouped_flow_table(root_ns, LEGACY_VEPA_PRIO,
						  2, 2, 0, 0);
	if (IS_ERR(fdb)) {
		err = PTR_ERR(fdb);
		esw_warn(dev, "Failed to create VEPA FDB err %d\n", err);
		return err;
	}
	esw->fdb_table.legacy.vepa_fdb = fdb;

	return 0;
}