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
struct TYPE_6__ {int /*<<< orphan*/  drop_icm_address_tx; int /*<<< orphan*/  drop_icm_address_rx; int /*<<< orphan*/  sw_owner; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vports_caps; scalar_t__ num_esw_ports; scalar_t__ num_vports; TYPE_3__ esw_caps; int /*<<< orphan*/  esw_tx_drop_address; int /*<<< orphan*/  esw_rx_drop_address; int /*<<< orphan*/  fdb_sw_owner; int /*<<< orphan*/  eswitch_manager; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;
struct mlx5dr_domain {TYPE_2__ info; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dr_domain_query_vports (struct mlx5dr_domain*) ; 
 int /*<<< orphan*/ * kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int mlx5dr_cmd_query_esw_caps (struct mlx5_core_dev*,TYPE_3__*) ; 
 int /*<<< orphan*/  mlx5dr_dbg (struct mlx5dr_domain*,char*) ; 

__attribute__((used)) static int dr_domain_query_fdb_caps(struct mlx5_core_dev *mdev,
				    struct mlx5dr_domain *dmn)
{
	int ret;

	if (!dmn->info.caps.eswitch_manager)
		return -EOPNOTSUPP;

	ret = mlx5dr_cmd_query_esw_caps(mdev, &dmn->info.caps.esw_caps);
	if (ret)
		return ret;

	dmn->info.caps.fdb_sw_owner = dmn->info.caps.esw_caps.sw_owner;
	dmn->info.caps.esw_rx_drop_address = dmn->info.caps.esw_caps.drop_icm_address_rx;
	dmn->info.caps.esw_tx_drop_address = dmn->info.caps.esw_caps.drop_icm_address_tx;

	dmn->info.caps.vports_caps = kcalloc(dmn->info.caps.num_esw_ports,
					     sizeof(dmn->info.caps.vports_caps[0]),
					     GFP_KERNEL);
	if (!dmn->info.caps.vports_caps)
		return -ENOMEM;

	ret = dr_domain_query_vports(dmn);
	if (ret) {
		mlx5dr_dbg(dmn, "Failed to query vports caps\n");
		goto free_vports_caps;
	}

	dmn->info.caps.num_vports = dmn->info.caps.num_esw_ports - 1;

	return 0;

free_vports_caps:
	kfree(dmn->info.caps.vports_caps);
	dmn->info.caps.vports_caps = NULL;
	return ret;
}