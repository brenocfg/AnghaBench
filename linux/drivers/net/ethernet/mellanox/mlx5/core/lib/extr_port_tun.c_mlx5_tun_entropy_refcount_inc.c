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
struct mlx5_tun_entropy {scalar_t__ num_disabling_entries; int /*<<< orphan*/  lock; int /*<<< orphan*/  num_enabling_entries; scalar_t__ enabled; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MLX5_REFORMAT_TYPE_L2_TO_NVGRE ; 
 int MLX5_REFORMAT_TYPE_L2_TO_VXLAN ; 
 int mlx5_set_entropy (struct mlx5_tun_entropy*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx5_tun_entropy_refcount_inc(struct mlx5_tun_entropy *tun_entropy,
				  int reformat_type)
{
	/* the default is error for unknown (non VXLAN/GRE tunnel types) */
	int err = -EOPNOTSUPP;

	mutex_lock(&tun_entropy->lock);
	if (reformat_type == MLX5_REFORMAT_TYPE_L2_TO_VXLAN &&
	    tun_entropy->enabled) {
		/* in case entropy calculation is enabled for all tunneling
		 * types, it is ok for VXLAN, so approve.
		 * otherwise keep the error default.
		 */
		tun_entropy->num_enabling_entries++;
		err = 0;
	} else if (reformat_type == MLX5_REFORMAT_TYPE_L2_TO_NVGRE) {
		/* turn off the entropy only for the first GRE rule.
		 * for the next rules the entropy was already disabled
		 * successfully.
		 */
		if (tun_entropy->num_disabling_entries == 0)
			err = mlx5_set_entropy(tun_entropy, reformat_type, 0);
		else
			err = 0;
		if (!err)
			tun_entropy->num_disabling_entries++;
	}
	mutex_unlock(&tun_entropy->lock);

	return err;
}