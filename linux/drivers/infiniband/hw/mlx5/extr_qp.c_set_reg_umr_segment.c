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
typedef  int u64 ;
struct mlx5_wqe_umr_ctrl_seg {int /*<<< orphan*/  mkey_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  xlt_offset_47_16; void* xlt_offset; void* xlt_octowords; } ;
struct mlx5_umr_wr {int /*<<< orphan*/  offset; int /*<<< orphan*/  xlt_size; int /*<<< orphan*/  ignore_free_state; } ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_send_wr {int send_flags; int /*<<< orphan*/  num_sge; } ;

/* Variables and functions */
 int MLX5_IB_SEND_UMR_DISABLE_MR ; 
 int MLX5_IB_SEND_UMR_ENABLE_MR ; 
 int MLX5_IB_SEND_UMR_FAIL_IF_FREE ; 
 int MLX5_IB_SEND_UMR_UPDATE_PD_ACCESS ; 
 int MLX5_IB_SEND_UMR_UPDATE_TRANSLATION ; 
 int MLX5_IB_SEND_UMR_UPDATE_XLT ; 
 int /*<<< orphan*/  MLX5_UMR_CHECK_FREE ; 
 int /*<<< orphan*/  MLX5_UMR_CHECK_NOT_FREE ; 
 int /*<<< orphan*/  MLX5_UMR_INLINE ; 
 int /*<<< orphan*/  MLX5_UMR_TRANSLATION_OFFSET_EN ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  get_umr_disable_mr_mask () ; 
 int /*<<< orphan*/  get_umr_enable_mr_mask () ; 
 int /*<<< orphan*/  get_umr_update_access_mask (int) ; 
 int /*<<< orphan*/  get_umr_update_pd_mask () ; 
 int /*<<< orphan*/  get_umr_update_translation_mask () ; 
 int get_xlt_octo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx5_wqe_umr_ctrl_seg*,int /*<<< orphan*/ ,int) ; 
 int umr_check_mkey_mask (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 struct mlx5_umr_wr* umr_wr (struct ib_send_wr const*) ; 

__attribute__((used)) static int set_reg_umr_segment(struct mlx5_ib_dev *dev,
			       struct mlx5_wqe_umr_ctrl_seg *umr,
			       const struct ib_send_wr *wr, int atomic)
{
	const struct mlx5_umr_wr *umrwr = umr_wr(wr);

	memset(umr, 0, sizeof(*umr));

	if (!umrwr->ignore_free_state) {
		if (wr->send_flags & MLX5_IB_SEND_UMR_FAIL_IF_FREE)
			 /* fail if free */
			umr->flags = MLX5_UMR_CHECK_FREE;
		else
			/* fail if not free */
			umr->flags = MLX5_UMR_CHECK_NOT_FREE;
	}

	umr->xlt_octowords = cpu_to_be16(get_xlt_octo(umrwr->xlt_size));
	if (wr->send_flags & MLX5_IB_SEND_UMR_UPDATE_XLT) {
		u64 offset = get_xlt_octo(umrwr->offset);

		umr->xlt_offset = cpu_to_be16(offset & 0xffff);
		umr->xlt_offset_47_16 = cpu_to_be32(offset >> 16);
		umr->flags |= MLX5_UMR_TRANSLATION_OFFSET_EN;
	}
	if (wr->send_flags & MLX5_IB_SEND_UMR_UPDATE_TRANSLATION)
		umr->mkey_mask |= get_umr_update_translation_mask();
	if (wr->send_flags & MLX5_IB_SEND_UMR_UPDATE_PD_ACCESS) {
		umr->mkey_mask |= get_umr_update_access_mask(atomic);
		umr->mkey_mask |= get_umr_update_pd_mask();
	}
	if (wr->send_flags & MLX5_IB_SEND_UMR_ENABLE_MR)
		umr->mkey_mask |= get_umr_enable_mr_mask();
	if (wr->send_flags & MLX5_IB_SEND_UMR_DISABLE_MR)
		umr->mkey_mask |= get_umr_disable_mr_mask();

	if (!wr->num_sge)
		umr->flags |= MLX5_UMR_INLINE;

	return umr_check_mkey_mask(dev, be64_to_cpu(umr->mkey_mask));
}