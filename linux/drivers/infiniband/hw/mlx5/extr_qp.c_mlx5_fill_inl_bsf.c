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
struct mlx5_bsf_inl {void* dif_app_bitmask_check; int /*<<< orphan*/  dif_inc_ref_guard_check; int /*<<< orphan*/  sig_type; int /*<<< orphan*/  rp_inv_seed; int /*<<< orphan*/  dif_reftag; void* dif_apptag; void* vld_refresh; } ;
struct TYPE_3__ {int app_tag; scalar_t__ bg_type; int apptag_check_mask; scalar_t__ ref_escape; scalar_t__ app_escape; scalar_t__ ref_remap; int /*<<< orphan*/  ref_tag; } ;
struct TYPE_4__ {TYPE_1__ dif; } ;
struct ib_sig_domain {TYPE_2__ sig; } ;

/* Variables and functions */
 scalar_t__ IB_T10DIF_CRC ; 
 int /*<<< orphan*/  MLX5_BSF_APPREF_ESCAPE ; 
 int /*<<< orphan*/  MLX5_BSF_APPTAG_ESCAPE ; 
 int /*<<< orphan*/  MLX5_BSF_INC_REFTAG ; 
 int MLX5_BSF_INL_VALID ; 
 int MLX5_BSF_REFRESH_DIF ; 
 int /*<<< orphan*/  MLX5_BSF_REPEAT_BLOCK ; 
 int /*<<< orphan*/  MLX5_DIF_CRC ; 
 int /*<<< orphan*/  MLX5_DIF_IPCS ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_fill_inl_bsf(struct ib_sig_domain *domain,
			      struct mlx5_bsf_inl *inl)
{
	/* Valid inline section and allow BSF refresh */
	inl->vld_refresh = cpu_to_be16(MLX5_BSF_INL_VALID |
				       MLX5_BSF_REFRESH_DIF);
	inl->dif_apptag = cpu_to_be16(domain->sig.dif.app_tag);
	inl->dif_reftag = cpu_to_be32(domain->sig.dif.ref_tag);
	/* repeating block */
	inl->rp_inv_seed = MLX5_BSF_REPEAT_BLOCK;
	inl->sig_type = domain->sig.dif.bg_type == IB_T10DIF_CRC ?
			MLX5_DIF_CRC : MLX5_DIF_IPCS;

	if (domain->sig.dif.ref_remap)
		inl->dif_inc_ref_guard_check |= MLX5_BSF_INC_REFTAG;

	if (domain->sig.dif.app_escape) {
		if (domain->sig.dif.ref_escape)
			inl->dif_inc_ref_guard_check |= MLX5_BSF_APPREF_ESCAPE;
		else
			inl->dif_inc_ref_guard_check |= MLX5_BSF_APPTAG_ESCAPE;
	}

	inl->dif_app_bitmask_check =
		cpu_to_be16(domain->sig.dif.apptag_check_mask);
}