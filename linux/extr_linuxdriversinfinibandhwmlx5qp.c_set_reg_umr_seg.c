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
struct mlx5_wqe_umr_ctrl_seg {int /*<<< orphan*/  mkey_mask; int /*<<< orphan*/  xlt_octowords; int /*<<< orphan*/  flags; } ;
struct mlx5_ib_mr {int ndescs; int desc_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_UMR_CHECK_NOT_FREE ; 
 int /*<<< orphan*/  MLX5_UMR_INLINE ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frwr_mkey_mask () ; 
 int /*<<< orphan*/  get_xlt_octo (int) ; 
 int /*<<< orphan*/  memset (struct mlx5_wqe_umr_ctrl_seg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_reg_umr_seg(struct mlx5_wqe_umr_ctrl_seg *umr,
			    struct mlx5_ib_mr *mr, bool umr_inline)
{
	int size = mr->ndescs * mr->desc_size;

	memset(umr, 0, sizeof(*umr));

	umr->flags = MLX5_UMR_CHECK_NOT_FREE;
	if (umr_inline)
		umr->flags |= MLX5_UMR_INLINE;
	umr->xlt_octowords = cpu_to_be16(get_xlt_octo(size));
	umr->mkey_mask = frwr_mkey_mask();
}