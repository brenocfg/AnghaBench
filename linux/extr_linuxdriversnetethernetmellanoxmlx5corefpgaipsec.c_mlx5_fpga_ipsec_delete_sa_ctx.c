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
struct mlx5_fpga_ipsec_sa_ctx {struct mlx5_fpga_esp_xfrm* fpga_xfrm; } ;
struct mlx5_fpga_esp_xfrm {int /*<<< orphan*/  lock; int /*<<< orphan*/ * sa_ctx; int /*<<< orphan*/  num_rules; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_fpga_ipsec_release_sa_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx5_fpga_ipsec_delete_sa_ctx(void *context)
{
	struct mlx5_fpga_esp_xfrm *fpga_xfrm =
			((struct mlx5_fpga_ipsec_sa_ctx *)context)->fpga_xfrm;

	mutex_lock(&fpga_xfrm->lock);
	if (!--fpga_xfrm->num_rules) {
		mlx5_fpga_ipsec_release_sa_ctx(fpga_xfrm->sa_ctx);
		fpga_xfrm->sa_ctx = NULL;
	}
	mutex_unlock(&fpga_xfrm->lock);
}