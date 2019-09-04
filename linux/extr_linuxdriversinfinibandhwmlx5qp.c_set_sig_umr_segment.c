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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_wqe_umr_ctrl_seg {int flags; int /*<<< orphan*/  mkey_mask; void* bsf_octowords; void* xlt_octowords; } ;

/* Variables and functions */
 int MLX5_FLAGS_CHECK_FREE ; 
 int MLX5_FLAGS_INLINE ; 
 int /*<<< orphan*/  MLX5_MKEY_BSF_OCTO_SIZE ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_xlt_octo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx5_wqe_umr_ctrl_seg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sig_mkey_mask () ; 

__attribute__((used)) static void set_sig_umr_segment(struct mlx5_wqe_umr_ctrl_seg *umr,
				u32 size)
{
	memset(umr, 0, sizeof(*umr));

	umr->flags = MLX5_FLAGS_INLINE | MLX5_FLAGS_CHECK_FREE;
	umr->xlt_octowords = cpu_to_be16(get_xlt_octo(size));
	umr->bsf_octowords = cpu_to_be16(MLX5_MKEY_BSF_OCTO_SIZE);
	umr->mkey_mask = sig_mkey_mask();
}