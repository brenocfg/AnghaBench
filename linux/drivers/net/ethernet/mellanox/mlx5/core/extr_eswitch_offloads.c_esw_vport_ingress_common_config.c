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
struct mlx5_vport {int /*<<< orphan*/  vport; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int esw_vport_add_ingress_acl_modify_metadata (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_cleanup_ingress_rules (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_disable_ingress_acl (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int esw_vport_enable_ingress_acl (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int esw_vport_ingress_prio_tag_config (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_eswitch_is_vf_vport (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_eswitch_vport_match_metadata_enabled (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  prio_tag_required ; 

__attribute__((used)) static int esw_vport_ingress_common_config(struct mlx5_eswitch *esw,
					   struct mlx5_vport *vport)
{
	int err;

	if (!mlx5_eswitch_vport_match_metadata_enabled(esw) &&
	    !MLX5_CAP_GEN(esw->dev, prio_tag_required))
		return 0;

	esw_vport_cleanup_ingress_rules(esw, vport);

	err = esw_vport_enable_ingress_acl(esw, vport);
	if (err) {
		esw_warn(esw->dev,
			 "failed to enable ingress acl (%d) on vport[%d]\n",
			 err, vport->vport);
		return err;
	}

	esw_debug(esw->dev,
		  "vport[%d] configure ingress rules\n", vport->vport);

	if (mlx5_eswitch_vport_match_metadata_enabled(esw)) {
		err = esw_vport_add_ingress_acl_modify_metadata(esw, vport);
		if (err)
			goto out;
	}

	if (MLX5_CAP_GEN(esw->dev, prio_tag_required) &&
	    mlx5_eswitch_is_vf_vport(esw, vport->vport)) {
		err = esw_vport_ingress_prio_tag_config(esw, vport);
		if (err)
			goto out;
	}

out:
	if (err)
		esw_vport_disable_ingress_acl(esw, vport);
	return err;
}