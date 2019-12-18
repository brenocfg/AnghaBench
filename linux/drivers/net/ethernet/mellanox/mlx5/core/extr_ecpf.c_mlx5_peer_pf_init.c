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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_peer_pf_enable_hca (struct mlx5_core_dev*) ; 

__attribute__((used)) static int mlx5_peer_pf_init(struct mlx5_core_dev *dev)
{
	int err;

	err = mlx5_peer_pf_enable_hca(dev);
	if (err)
		mlx5_core_err(dev, "Failed to enable peer PF HCA err(%d)\n",
			      err);

	return err;
}