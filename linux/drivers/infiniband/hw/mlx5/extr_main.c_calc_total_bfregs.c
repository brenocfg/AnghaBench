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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_ib_alloc_ucontext_req_v2 {int total_num_bfregs; scalar_t__ num_low_latency_bfregs; } ;
struct mlx5_bfreg_info {int num_static_sys_pages; int num_dyn_bfregs; int total_num_bfregs; int num_sys_pages; } ;

/* Variables and functions */
 void* ALIGN (int,int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_MAX_BFREGS ; 
 int MLX5_NON_FP_BFREGS_IN_PAGE ; 
 int MLX5_NON_FP_BFREGS_PER_UAR ; 
 int calc_dynamic_bfregs (int) ; 
 int get_uars_per_sys_page (struct mlx5_ib_dev*,int) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  uar_4k ; 

__attribute__((used)) static int calc_total_bfregs(struct mlx5_ib_dev *dev, bool lib_uar_4k,
			     struct mlx5_ib_alloc_ucontext_req_v2 *req,
			     struct mlx5_bfreg_info *bfregi)
{
	int uars_per_sys_page;
	int bfregs_per_sys_page;
	int ref_bfregs = req->total_num_bfregs;

	if (req->total_num_bfregs == 0)
		return -EINVAL;

	BUILD_BUG_ON(MLX5_MAX_BFREGS % MLX5_NON_FP_BFREGS_IN_PAGE);
	BUILD_BUG_ON(MLX5_MAX_BFREGS < MLX5_NON_FP_BFREGS_IN_PAGE);

	if (req->total_num_bfregs > MLX5_MAX_BFREGS)
		return -ENOMEM;

	uars_per_sys_page = get_uars_per_sys_page(dev, lib_uar_4k);
	bfregs_per_sys_page = uars_per_sys_page * MLX5_NON_FP_BFREGS_PER_UAR;
	/* This holds the required static allocation asked by the user */
	req->total_num_bfregs = ALIGN(req->total_num_bfregs, bfregs_per_sys_page);
	if (req->num_low_latency_bfregs > req->total_num_bfregs - 1)
		return -EINVAL;

	bfregi->num_static_sys_pages = req->total_num_bfregs / bfregs_per_sys_page;
	bfregi->num_dyn_bfregs = ALIGN(calc_dynamic_bfregs(uars_per_sys_page), bfregs_per_sys_page);
	bfregi->total_num_bfregs = req->total_num_bfregs + bfregi->num_dyn_bfregs;
	bfregi->num_sys_pages = bfregi->total_num_bfregs / bfregs_per_sys_page;

	mlx5_ib_dbg(dev, "uar_4k: fw support %s, lib support %s, user requested %d bfregs, allocated %d, total bfregs %d, using %d sys pages\n",
		    MLX5_CAP_GEN(dev->mdev, uar_4k) ? "yes" : "no",
		    lib_uar_4k ? "yes" : "no", ref_bfregs,
		    req->total_num_bfregs, bfregi->total_num_bfregs,
		    bfregi->num_sys_pages);

	return 0;
}