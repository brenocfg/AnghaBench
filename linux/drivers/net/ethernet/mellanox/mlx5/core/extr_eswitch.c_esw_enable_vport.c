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
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int trusted; int /*<<< orphan*/  max_rate; } ;
struct TYPE_3__ {int /*<<< orphan*/  bw_share; } ;
struct mlx5_vport {scalar_t__ vport; int enabled; int enabled_events; TYPE_2__ info; TYPE_1__ qos; } ;
struct mlx5_eswitch {scalar_t__ mode; scalar_t__ manager_vport; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  enabled_vports; } ;
typedef  enum mlx5_eswitch_vport_event { ____Placeholder_mlx5_eswitch_vport_event } mlx5_eswitch_vport_event ;

/* Variables and functions */
 scalar_t__ MLX5_ESWITCH_LEGACY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  esw_apply_vport_conf (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_debug (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  esw_vport_change_handle_locked (struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_create_drop_counters (struct mlx5_vport*) ; 
 scalar_t__ esw_vport_enable_qos (struct mlx5_eswitch*,struct mlx5_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ mlx5_core_is_ecpf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esw_enable_vport(struct mlx5_eswitch *esw, struct mlx5_vport *vport,
			     enum mlx5_eswitch_vport_event enabled_events)
{
	u16 vport_num = vport->vport;

	mutex_lock(&esw->state_lock);
	WARN_ON(vport->enabled);

	esw_debug(esw->dev, "Enabling VPORT(%d)\n", vport_num);

	/* Create steering drop counters for ingress and egress ACLs */
	if (vport_num && esw->mode == MLX5_ESWITCH_LEGACY)
		esw_vport_create_drop_counters(vport);

	/* Restore old vport configuration */
	esw_apply_vport_conf(esw, vport);

	/* Attach vport to the eswitch rate limiter */
	if (esw_vport_enable_qos(esw, vport, vport->info.max_rate,
				 vport->qos.bw_share))
		esw_warn(esw->dev, "Failed to attach vport %d to eswitch rate limiter", vport_num);

	/* Sync with current vport context */
	vport->enabled_events = enabled_events;
	vport->enabled = true;

	/* Esw manager is trusted by default. Host PF (vport 0) is trusted as well
	 * in smartNIC as it's a vport group manager.
	 */
	if (esw->manager_vport == vport_num ||
	    (!vport_num && mlx5_core_is_ecpf(esw->dev)))
		vport->info.trusted = true;

	esw_vport_change_handle_locked(vport);

	esw->enabled_vports++;
	esw_debug(esw->dev, "Enabled VPORT(%d)\n", vport_num);
	mutex_unlock(&esw->state_lock);
}