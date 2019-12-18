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
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ vepa_uplink_rule; } ;
struct TYPE_4__ {TYPE_1__ legacy; } ;
struct mlx5_eswitch {scalar_t__ mode; int /*<<< orphan*/  state_lock; TYPE_2__ fdb_table; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  ESW_ALLOWED (struct mlx5_eswitch*) ; 
 scalar_t__ MLX5_ESWITCH_LEGACY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx5_eswitch_get_vepa(struct mlx5_eswitch *esw, u8 *setting)
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

	*setting = esw->fdb_table.legacy.vepa_uplink_rule ? 1 : 0;

out:
	mutex_unlock(&esw->state_lock);
	return err;
}