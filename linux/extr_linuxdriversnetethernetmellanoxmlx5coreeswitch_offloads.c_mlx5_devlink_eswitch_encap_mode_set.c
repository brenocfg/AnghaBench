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
typedef  void* u8 ;
struct TYPE_4__ {void* encap; scalar_t__ num_flows; } ;
struct mlx5_eswitch {scalar_t__ mode; TYPE_2__ offloads; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct mlx5_eswitch* eswitch; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 void* DEVLINK_ESWITCH_ENCAP_MODE_BASIC ; 
 void* DEVLINK_ESWITCH_ENCAP_MODE_NONE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5_CAP_ESW_FLOWTABLE_FDB (struct mlx5_core_dev*,void*) ; 
 scalar_t__ SRIOV_LEGACY ; 
 void* decap ; 
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int esw_create_offloads_fast_fdb_table (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_destroy_offloads_fast_fdb_table (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_warn (struct mlx5_core_dev*,char*,...) ; 
 int mlx5_devlink_eswitch_check (struct devlink*) ; 

int mlx5_devlink_eswitch_encap_mode_set(struct devlink *devlink, u8 encap)
{
	struct mlx5_core_dev *dev = devlink_priv(devlink);
	struct mlx5_eswitch *esw = dev->priv.eswitch;
	int err;

	err = mlx5_devlink_eswitch_check(devlink);
	if (err)
		return err;

	if (encap != DEVLINK_ESWITCH_ENCAP_MODE_NONE &&
	    (!MLX5_CAP_ESW_FLOWTABLE_FDB(dev, encap) ||
	     !MLX5_CAP_ESW_FLOWTABLE_FDB(dev, decap)))
		return -EOPNOTSUPP;

	if (encap && encap != DEVLINK_ESWITCH_ENCAP_MODE_BASIC)
		return -EOPNOTSUPP;

	if (esw->mode == SRIOV_LEGACY) {
		esw->offloads.encap = encap;
		return 0;
	}

	if (esw->offloads.encap == encap)
		return 0;

	if (esw->offloads.num_flows > 0) {
		esw_warn(dev, "Can't set encapsulation when flows are configured\n");
		return -EOPNOTSUPP;
	}

	esw_destroy_offloads_fast_fdb_table(esw);

	esw->offloads.encap = encap;
	err = esw_create_offloads_fast_fdb_table(esw);
	if (err) {
		esw_warn(esw->dev, "Failed re-creating fast FDB table, err %d\n", err);
		esw->offloads.encap = !encap;
		(void)esw_create_offloads_fast_fdb_table(esw);
	}
	return err;
}