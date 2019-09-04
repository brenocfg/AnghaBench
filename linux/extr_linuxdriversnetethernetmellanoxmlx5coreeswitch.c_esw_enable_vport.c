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
struct TYPE_4__ {int trusted; int /*<<< orphan*/  max_rate; } ;
struct TYPE_3__ {int /*<<< orphan*/  bw_share; } ;
struct mlx5_vport {int enabled; int enabled_events; TYPE_2__ info; TYPE_1__ qos; } ;
struct mlx5_eswitch {scalar_t__ mode; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  enabled_vports; struct mlx5_vport* vports; } ;

/* Variables and functions */
 scalar_t__ SRIOV_LEGACY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  esw_apply_vport_conf (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  esw_vport_change_handle_locked (struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_create_drop_counters (struct mlx5_vport*) ; 
 scalar_t__ esw_vport_enable_qos (struct mlx5_eswitch*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esw_enable_vport(struct mlx5_eswitch *esw, int vport_num,
			     int enable_events)
{
	struct mlx5_vport *vport = &esw->vports[vport_num];

	mutex_lock(&esw->state_lock);
	WARN_ON(vport->enabled);

	esw_debug(esw->dev, "Enabling VPORT(%d)\n", vport_num);

	/* Create steering drop counters for ingress and egress ACLs */
	if (vport_num && esw->mode == SRIOV_LEGACY)
		esw_vport_create_drop_counters(vport);

	/* Restore old vport configuration */
	esw_apply_vport_conf(esw, vport);

	/* Attach vport to the eswitch rate limiter */
	if (esw_vport_enable_qos(esw, vport_num, vport->info.max_rate,
				 vport->qos.bw_share))
		esw_warn(esw->dev, "Failed to attach vport %d to eswitch rate limiter", vport_num);

	/* Sync with current vport context */
	vport->enabled_events = enable_events;
	vport->enabled = true;

	/* only PF is trusted by default */
	if (!vport_num)
		vport->info.trusted = true;

	esw_vport_change_handle_locked(vport);

	esw->enabled_vports++;
	esw_debug(esw->dev, "Enabled VPORT(%d)\n", vport_num);
	mutex_unlock(&esw->state_lock);
}