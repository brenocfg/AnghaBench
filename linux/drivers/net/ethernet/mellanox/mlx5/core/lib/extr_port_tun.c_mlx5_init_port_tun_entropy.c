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
struct mlx5_tun_entropy {int enabled; scalar_t__ num_disabling_entries; scalar_t__ num_enabling_entries; int /*<<< orphan*/  lock; struct mlx5_core_dev* mdev; } ;
struct mlx5_port_tun_entropy_flags {int calc_enabled; scalar_t__ calc_supported; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_query_port_tun_entropy (struct mlx5_core_dev*,struct mlx5_port_tun_entropy_flags*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void mlx5_init_port_tun_entropy(struct mlx5_tun_entropy *tun_entropy,
				struct mlx5_core_dev *mdev)
{
	struct mlx5_port_tun_entropy_flags entropy_flags;

	tun_entropy->mdev = mdev;
	mutex_init(&tun_entropy->lock);
	mlx5_query_port_tun_entropy(mdev, &entropy_flags);
	tun_entropy->num_enabling_entries = 0;
	tun_entropy->num_disabling_entries = 0;
	tun_entropy->enabled = entropy_flags.calc_supported ?
			       entropy_flags.calc_enabled : true;
}