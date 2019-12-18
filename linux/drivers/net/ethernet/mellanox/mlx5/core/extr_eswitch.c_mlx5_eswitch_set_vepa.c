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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_eswitch {scalar_t__ mode; int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  ESW_ALLOWED (struct mlx5_eswitch*) ; 
 scalar_t__ MLX5_ESWITCH_LEGACY ; 
 int _mlx5_eswitch_set_vepa_locked (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx5_eswitch_set_vepa(struct mlx5_eswitch *esw, u8 setting)
{
	int err = 0;

	if (!esw)
		return -EOPNOTSUPP;

	if (!ESW_ALLOWED(esw))
		return -EPERM;

	mutex_lock(&esw->state_lock);
	if (esw->mode != MLX5_ESWITCH_LEGACY) {
		err = -EOPNOTSUPP;
		goto out;
	}

	err = _mlx5_eswitch_set_vepa_locked(esw, setting);

out:
	mutex_unlock(&esw->state_lock);
	return err;
}