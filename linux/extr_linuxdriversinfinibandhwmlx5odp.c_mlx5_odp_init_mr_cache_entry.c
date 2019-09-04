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
struct mlx5_mtt {int dummy; } ;
struct mlx5_klm {int dummy; } ;
struct mlx5_cache_ent {int order; int xlt; int /*<<< orphan*/  limit; int /*<<< orphan*/  access_mode; int /*<<< orphan*/  page; TYPE_2__* dev; } ;
struct TYPE_3__ {int general_caps; } ;
struct TYPE_4__ {TYPE_1__ odp_caps; } ;

/* Variables and functions */
 int IB_ODP_SUPPORT_IMPLICIT ; 
 int MLX5_IB_UMR_OCTOWORD ; 
#define  MLX5_IMR_KSM_CACHE_ENTRY 129 
#define  MLX5_IMR_MTT_CACHE_ENTRY 128 
 int MLX5_IMR_MTT_ENTRIES ; 
 int /*<<< orphan*/  MLX5_KSM_PAGE_SHIFT ; 
 int /*<<< orphan*/  MLX5_MKC_ACCESS_MODE_KSM ; 
 int /*<<< orphan*/  MLX5_MKC_ACCESS_MODE_MTT ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int mlx5_imr_ksm_entries ; 

void mlx5_odp_init_mr_cache_entry(struct mlx5_cache_ent *ent)
{
	if (!(ent->dev->odp_caps.general_caps & IB_ODP_SUPPORT_IMPLICIT))
		return;

	switch (ent->order - 2) {
	case MLX5_IMR_MTT_CACHE_ENTRY:
		ent->page = PAGE_SHIFT;
		ent->xlt = MLX5_IMR_MTT_ENTRIES *
			   sizeof(struct mlx5_mtt) /
			   MLX5_IB_UMR_OCTOWORD;
		ent->access_mode = MLX5_MKC_ACCESS_MODE_MTT;
		ent->limit = 0;
		break;

	case MLX5_IMR_KSM_CACHE_ENTRY:
		ent->page = MLX5_KSM_PAGE_SHIFT;
		ent->xlt = mlx5_imr_ksm_entries *
			   sizeof(struct mlx5_klm) /
			   MLX5_IB_UMR_OCTOWORD;
		ent->access_mode = MLX5_MKC_ACCESS_MODE_KSM;
		ent->limit = 0;
		break;
	}
}