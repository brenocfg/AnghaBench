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
struct netlink_ext_ack {int dummy; } ;
struct TYPE_4__ {int encap; int /*<<< orphan*/  num_flows; } ;
struct mlx5_eswitch {scalar_t__ mode; int /*<<< orphan*/  nvports; TYPE_2__ offloads; } ;
struct TYPE_3__ {struct mlx5_eswitch* eswitch; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_eswitch_encap_mode { ____Placeholder_devlink_eswitch_encap_mode } devlink_eswitch_encap_mode ;

/* Variables and functions */
 int DEVLINK_ESWITCH_ENCAP_MODE_BASIC ; 
 int DEVLINK_ESWITCH_ENCAP_MODE_NONE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5_CAP_ESW_FLOWTABLE_FDB (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_ESWITCH_LEGACY ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decap ; 
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int esw_create_offloads_fdb_tables (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_destroy_offloads_fdb_tables (struct mlx5_eswitch*) ; 
 int mlx5_devlink_eswitch_check (struct devlink*) ; 
 int /*<<< orphan*/  reformat ; 

int mlx5_devlink_eswitch_encap_mode_set(struct devlink *devlink,
					enum devlink_eswitch_encap_mode encap,
					struct netlink_ext_ack *extack)
{
	struct mlx5_core_dev *dev = devlink_priv(devlink);
	struct mlx5_eswitch *esw = dev->priv.eswitch;
	int err;

	err = mlx5_devlink_eswitch_check(devlink);
	if (err)
		return err;

	if (encap != DEVLINK_ESWITCH_ENCAP_MODE_NONE &&
	    (!MLX5_CAP_ESW_FLOWTABLE_FDB(dev, reformat) ||
	     !MLX5_CAP_ESW_FLOWTABLE_FDB(dev, decap)))
		return -EOPNOTSUPP;

	if (encap && encap != DEVLINK_ESWITCH_ENCAP_MODE_BASIC)
		return -EOPNOTSUPP;

	if (esw->mode == MLX5_ESWITCH_LEGACY) {
		esw->offloads.encap = encap;
		return 0;
	}

	if (esw->offloads.encap == encap)
		return 0;

	if (atomic64_read(&esw->offloads.num_flows) > 0) {
		NL_SET_ERR_MSG_MOD(extack,
				   "Can't set encapsulation when flows are configured");
		return -EOPNOTSUPP;
	}

	esw_destroy_offloads_fdb_tables(esw);

	esw->offloads.encap = encap;

	err = esw_create_offloads_fdb_tables(esw, esw->nvports);

	if (err) {
		NL_SET_ERR_MSG_MOD(extack,
				   "Failed re-creating fast FDB table");
		esw->offloads.encap = !encap;
		(void)esw_create_offloads_fdb_tables(esw, esw->nvports);
	}

	return err;
}