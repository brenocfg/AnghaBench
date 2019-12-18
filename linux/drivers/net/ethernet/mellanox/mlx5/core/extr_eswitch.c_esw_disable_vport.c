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
typedef  scalar_t__ u16 ;
struct mlx5_vport {scalar_t__ vport; int enabled; scalar_t__ enabled_events; } ;
struct mlx5_eswitch {scalar_t__ manager_vport; scalar_t__ mode; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  enabled_vports; int /*<<< orphan*/  dev; int /*<<< orphan*/  work_queue; } ;

/* Variables and functions */
 scalar_t__ MLX5_ESWITCH_LEGACY ; 
 int /*<<< orphan*/  MLX5_VPORT_ADMIN_STATE_DOWN ; 
 int /*<<< orphan*/  MLX5_VPORT_STATE_OP_MOD_ESW_VPORT ; 
 int /*<<< orphan*/  arm_vport_context_events_cmd (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_debug (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  esw_vport_change_handle_locked (struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_destroy_drop_counters (struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_disable_egress_acl (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_disable_ingress_acl (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_disable_qos (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_modify_vport_admin_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esw_disable_vport(struct mlx5_eswitch *esw,
			      struct mlx5_vport *vport)
{
	u16 vport_num = vport->vport;

	if (!vport->enabled)
		return;

	esw_debug(esw->dev, "Disabling vport(%d)\n", vport_num);
	/* Mark this vport as disabled to discard new events */
	vport->enabled = false;

	/* Wait for current already scheduled events to complete */
	flush_workqueue(esw->work_queue);
	/* Disable events from this vport */
	arm_vport_context_events_cmd(esw->dev, vport->vport, 0);
	mutex_lock(&esw->state_lock);
	/* We don't assume VFs will cleanup after themselves.
	 * Calling vport change handler while vport is disabled will cleanup
	 * the vport resources.
	 */
	esw_vport_change_handle_locked(vport);
	vport->enabled_events = 0;
	esw_vport_disable_qos(esw, vport);
	if (esw->manager_vport != vport_num &&
	    esw->mode == MLX5_ESWITCH_LEGACY) {
		mlx5_modify_vport_admin_state(esw->dev,
					      MLX5_VPORT_STATE_OP_MOD_ESW_VPORT,
					      vport_num, 1,
					      MLX5_VPORT_ADMIN_STATE_DOWN);
		esw_vport_disable_egress_acl(esw, vport);
		esw_vport_disable_ingress_acl(esw, vport);
		esw_vport_destroy_drop_counters(vport);
	}
	esw->enabled_vports--;
	mutex_unlock(&esw->state_lock);
}