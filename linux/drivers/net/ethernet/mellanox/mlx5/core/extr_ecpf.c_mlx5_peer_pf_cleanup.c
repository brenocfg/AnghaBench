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
struct TYPE_2__ {int /*<<< orphan*/  peer_pf_pages; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_peer_pf_disable_hca (struct mlx5_core_dev*) ; 
 int mlx5_wait_for_pages (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_peer_pf_cleanup(struct mlx5_core_dev *dev)
{
	int err;

	err = mlx5_peer_pf_disable_hca(dev);
	if (err) {
		mlx5_core_err(dev, "Failed to disable peer PF HCA err(%d)\n",
			      err);
		return;
	}

	err = mlx5_wait_for_pages(dev, &dev->priv.peer_pf_pages);
	if (err)
		mlx5_core_warn(dev, "Timeout reclaiming peer PF pages err(%d)\n",
			       err);
}