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
struct mlx5dr_domain {int /*<<< orphan*/  pdn; int /*<<< orphan*/  mdev; int /*<<< orphan*/  uar; int /*<<< orphan*/  ste_icm_pool; int /*<<< orphan*/  action_icm_pool; int /*<<< orphan*/  send_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_dealloc_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_put_uars_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_icm_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_send_ring_free (struct mlx5dr_domain*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dr_domain_uninit_resources(struct mlx5dr_domain *dmn)
{
	mlx5dr_send_ring_free(dmn, dmn->send_ring);
	mlx5dr_icm_pool_destroy(dmn->action_icm_pool);
	mlx5dr_icm_pool_destroy(dmn->ste_icm_pool);
	mlx5_put_uars_page(dmn->mdev, dmn->uar);
	mlx5_core_dealloc_pd(dmn->mdev, dmn->pdn);
}