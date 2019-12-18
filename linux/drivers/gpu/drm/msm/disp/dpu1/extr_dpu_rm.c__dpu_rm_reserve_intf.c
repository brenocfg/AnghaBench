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
typedef  scalar_t__ uint32_t ;
struct dpu_rm_hw_iter {int /*<<< orphan*/  hw; TYPE_1__* blk; } ;
struct dpu_rm {int dummy; } ;
typedef  enum dpu_hw_blk_type { ____Placeholder_dpu_hw_blk_type } dpu_hw_blk_type ;
struct TYPE_2__ {scalar_t__ id; scalar_t__ enc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*,int,scalar_t__) ; 
 int EINVAL ; 
 int ENAVAIL ; 
 scalar_t__ RESERVED_BY_OTHER (TYPE_1__*,scalar_t__) ; 
 scalar_t__ _dpu_rm_get_hw_locked (struct dpu_rm*,struct dpu_rm_hw_iter*) ; 
 int /*<<< orphan*/  dpu_rm_init_hw_iter (struct dpu_rm_hw_iter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_dpu_rm_reserve_intf (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int _dpu_rm_reserve_intf(
		struct dpu_rm *rm,
		uint32_t enc_id,
		uint32_t id,
		enum dpu_hw_blk_type type)
{
	struct dpu_rm_hw_iter iter;
	int ret = 0;

	/* Find the block entry in the rm, and note the reservation */
	dpu_rm_init_hw_iter(&iter, 0, type);
	while (_dpu_rm_get_hw_locked(rm, &iter)) {
		if (iter.blk->id != id)
			continue;

		if (RESERVED_BY_OTHER(iter.blk, enc_id)) {
			DPU_ERROR("type %d id %d already reserved\n", type, id);
			return -ENAVAIL;
		}

		iter.blk->enc_id = enc_id;
		trace_dpu_rm_reserve_intf(iter.blk->id, enc_id);
		break;
	}

	/* Shouldn't happen since intfs are fixed at probe */
	if (!iter.hw) {
		DPU_ERROR("couldn't find type %d id %d\n", type, id);
		return -EINVAL;
	}

	return ret;
}