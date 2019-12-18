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
typedef  int /*<<< orphan*/  uint32_t ;
struct dpu_rm_requirements {int dummy; } ;
struct dpu_rm_hw_iter {struct dpu_rm_hw_blk* blk; } ;
struct dpu_rm_hw_blk {scalar_t__ id; int /*<<< orphan*/  hw; } ;
struct dpu_rm {int dummy; } ;
struct dpu_lm_cfg {scalar_t__ id; scalar_t__ pingpong; int /*<<< orphan*/  lm_pair_mask; } ;
struct TYPE_2__ {struct dpu_lm_cfg* cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  DPU_HW_BLK_PINGPONG ; 
 scalar_t__ RESERVED_BY_OTHER (struct dpu_rm_hw_blk*,int /*<<< orphan*/ ) ; 
 scalar_t__ _dpu_rm_get_hw_locked (struct dpu_rm*,struct dpu_rm_hw_iter*) ; 
 int /*<<< orphan*/  dpu_rm_init_hw_iter (struct dpu_rm_hw_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__* to_dpu_hw_mixer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool _dpu_rm_check_lm_and_get_connected_blks(
		struct dpu_rm *rm,
		uint32_t enc_id,
		struct dpu_rm_requirements *reqs,
		struct dpu_rm_hw_blk *lm,
		struct dpu_rm_hw_blk **pp,
		struct dpu_rm_hw_blk *primary_lm)
{
	const struct dpu_lm_cfg *lm_cfg = to_dpu_hw_mixer(lm->hw)->cap;
	struct dpu_rm_hw_iter iter;

	*pp = NULL;

	DPU_DEBUG("check lm %d pp %d\n",
			   lm_cfg->id, lm_cfg->pingpong);

	/* Check if this layer mixer is a peer of the proposed primary LM */
	if (primary_lm) {
		const struct dpu_lm_cfg *prim_lm_cfg =
				to_dpu_hw_mixer(primary_lm->hw)->cap;

		if (!test_bit(lm_cfg->id, &prim_lm_cfg->lm_pair_mask)) {
			DPU_DEBUG("lm %d not peer of lm %d\n", lm_cfg->id,
					prim_lm_cfg->id);
			return false;
		}
	}

	/* Already reserved? */
	if (RESERVED_BY_OTHER(lm, enc_id)) {
		DPU_DEBUG("lm %d already reserved\n", lm_cfg->id);
		return false;
	}

	dpu_rm_init_hw_iter(&iter, 0, DPU_HW_BLK_PINGPONG);
	while (_dpu_rm_get_hw_locked(rm, &iter)) {
		if (iter.blk->id == lm_cfg->pingpong) {
			*pp = iter.blk;
			break;
		}
	}

	if (!*pp) {
		DPU_ERROR("failed to get pp on lm %d\n", lm_cfg->pingpong);
		return false;
	}

	if (RESERVED_BY_OTHER(*pp, enc_id)) {
		DPU_DEBUG("lm %d pp %d already reserved\n", lm->id,
				(*pp)->id);
		return false;
	}

	return true;
}