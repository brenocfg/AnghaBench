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
struct TYPE_2__ {int trusted; } ;
struct mlx5_vport {scalar_t__ enabled; TYPE_1__ info; } ;
struct mlx5_eswitch {int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  ESW_ALLOWED (struct mlx5_eswitch*) ; 
 scalar_t__ IS_ERR (struct mlx5_vport*) ; 
 int PTR_ERR (struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_change_handle_locked (struct mlx5_vport*) ; 
 struct mlx5_vport* mlx5_eswitch_get_vport (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx5_eswitch_set_vport_trust(struct mlx5_eswitch *esw,
				 u16 vport, bool setting)
{
	struct mlx5_vport *evport = mlx5_eswitch_get_vport(esw, vport);

	if (!ESW_ALLOWED(esw))
		return -EPERM;
	if (IS_ERR(evport))
		return PTR_ERR(evport);

	mutex_lock(&esw->state_lock);
	evport->info.trusted = setting;
	if (evport->enabled)
		esw_vport_change_handle_locked(evport);
	mutex_unlock(&esw->state_lock);

	return 0;
}