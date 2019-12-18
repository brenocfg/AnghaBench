#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_13__ {int /*<<< orphan*/  psv_idx; } ;
struct TYPE_9__ {int /*<<< orphan*/  psv_idx; } ;
struct mlx5_core_sig_ctx {TYPE_6__ psv_wire; TYPE_2__ psv_memory; } ;
struct TYPE_10__ {void* bs_selector; int /*<<< orphan*/  copy_byte_mask; } ;
struct TYPE_8__ {void* bs_selector; } ;
struct mlx5_bsf_basic {int bsf_size_sbs; void* w_bfs_psv; TYPE_3__ wire; void* m_bfs_psv; TYPE_1__ mem; void* raw_data_size; int /*<<< orphan*/  check_byte_mask; } ;
struct mlx5_bsf {int /*<<< orphan*/  w_inl; int /*<<< orphan*/  m_inl; struct mlx5_bsf_basic basic; } ;
struct TYPE_11__ {int /*<<< orphan*/  pi_interval; int /*<<< orphan*/  ref_tag; int /*<<< orphan*/  app_tag; int /*<<< orphan*/  bg_type; } ;
struct TYPE_12__ {TYPE_4__ dif; } ;
struct ib_sig_domain {int sig_type; TYPE_5__ sig; } ;
struct ib_sig_attrs {struct ib_sig_domain wire; struct ib_sig_domain mem; int /*<<< orphan*/  check_mask; } ;
struct ib_mr {int dummy; } ;
struct TYPE_14__ {struct mlx5_core_sig_ctx* sig; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_SIG_TYPE_NONE 129 
#define  IB_SIG_TYPE_T10_DIF 128 
 int /*<<< orphan*/  MLX5_CPY_APP_MASK ; 
 int /*<<< orphan*/  MLX5_CPY_GRD_MASK ; 
 int /*<<< orphan*/  MLX5_CPY_REF_MASK ; 
 void* bs_selector (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx5_bsf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_fill_inl_bsf (struct ib_sig_domain*,int /*<<< orphan*/ *) ; 
 TYPE_7__* to_mmr (struct ib_mr*) ; 

__attribute__((used)) static int mlx5_set_bsf(struct ib_mr *sig_mr,
			struct ib_sig_attrs *sig_attrs,
			struct mlx5_bsf *bsf, u32 data_size)
{
	struct mlx5_core_sig_ctx *msig = to_mmr(sig_mr)->sig;
	struct mlx5_bsf_basic *basic = &bsf->basic;
	struct ib_sig_domain *mem = &sig_attrs->mem;
	struct ib_sig_domain *wire = &sig_attrs->wire;

	memset(bsf, 0, sizeof(*bsf));

	/* Basic + Extended + Inline */
	basic->bsf_size_sbs = 1 << 7;
	/* Input domain check byte mask */
	basic->check_byte_mask = sig_attrs->check_mask;
	basic->raw_data_size = cpu_to_be32(data_size);

	/* Memory domain */
	switch (sig_attrs->mem.sig_type) {
	case IB_SIG_TYPE_NONE:
		break;
	case IB_SIG_TYPE_T10_DIF:
		basic->mem.bs_selector = bs_selector(mem->sig.dif.pi_interval);
		basic->m_bfs_psv = cpu_to_be32(msig->psv_memory.psv_idx);
		mlx5_fill_inl_bsf(mem, &bsf->m_inl);
		break;
	default:
		return -EINVAL;
	}

	/* Wire domain */
	switch (sig_attrs->wire.sig_type) {
	case IB_SIG_TYPE_NONE:
		break;
	case IB_SIG_TYPE_T10_DIF:
		if (mem->sig.dif.pi_interval == wire->sig.dif.pi_interval &&
		    mem->sig_type == wire->sig_type) {
			/* Same block structure */
			basic->bsf_size_sbs |= 1 << 4;
			if (mem->sig.dif.bg_type == wire->sig.dif.bg_type)
				basic->wire.copy_byte_mask |= MLX5_CPY_GRD_MASK;
			if (mem->sig.dif.app_tag == wire->sig.dif.app_tag)
				basic->wire.copy_byte_mask |= MLX5_CPY_APP_MASK;
			if (mem->sig.dif.ref_tag == wire->sig.dif.ref_tag)
				basic->wire.copy_byte_mask |= MLX5_CPY_REF_MASK;
		} else
			basic->wire.bs_selector = bs_selector(wire->sig.dif.pi_interval);

		basic->w_bfs_psv = cpu_to_be32(msig->psv_wire.psv_idx);
		mlx5_fill_inl_bsf(wire, &bsf->w_inl);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}