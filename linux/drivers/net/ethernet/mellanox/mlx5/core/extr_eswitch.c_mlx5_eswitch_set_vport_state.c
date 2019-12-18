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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int link_state; } ;
struct mlx5_vport {TYPE_1__ info; } ;
struct mlx5_eswitch {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  ESW_ALLOWED (struct mlx5_eswitch*) ; 
 scalar_t__ IS_ERR (struct mlx5_vport*) ; 
 int /*<<< orphan*/  MLX5_VPORT_STATE_OP_MOD_ESW_VPORT ; 
 int PTR_ERR (struct mlx5_vport*) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct mlx5_vport* mlx5_eswitch_get_vport (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int mlx5_modify_vport_admin_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx5_eswitch_set_vport_state(struct mlx5_eswitch *esw,
				 u16 vport, int link_state)
{
	struct mlx5_vport *evport = mlx5_eswitch_get_vport(esw, vport);
	int err = 0;

	if (!ESW_ALLOWED(esw))
		return -EPERM;
	if (IS_ERR(evport))
		return PTR_ERR(evport);

	mutex_lock(&esw->state_lock);

	err = mlx5_modify_vport_admin_state(esw->dev,
					    MLX5_VPORT_STATE_OP_MOD_ESW_VPORT,
					    vport, 1, link_state);
	if (err) {
		mlx5_core_warn(esw->dev,
			       "Failed to set vport %d link state, err = %d",
			       vport, err);
		goto unlock;
	}

	evport->info.link_state = link_state;

unlock:
	mutex_unlock(&esw->state_lock);
	return 0;
}