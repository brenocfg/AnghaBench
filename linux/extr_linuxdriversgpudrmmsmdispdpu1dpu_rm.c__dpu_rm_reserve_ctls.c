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
struct dpu_rm_topology_def {int needs_split_display; int num_ctl; } ;
struct dpu_rm_rsvp {int /*<<< orphan*/  enc_id; } ;
struct dpu_rm_hw_iter {struct dpu_rm_hw_blk* blk; } ;
struct dpu_rm_hw_blk {int /*<<< orphan*/  type; int /*<<< orphan*/  id; struct dpu_rm_rsvp* rsvp_nxt; int /*<<< orphan*/  hw; } ;
struct dpu_rm {int dummy; } ;
struct dpu_hw_ctl {TYPE_1__* caps; } ;
typedef  int /*<<< orphan*/  ctls ;
struct TYPE_2__ {unsigned long features; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dpu_rm_hw_blk**) ; 
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_CTL_SPLIT_DISPLAY ; 
 int /*<<< orphan*/  DPU_DEBUG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DPU_HW_BLK_CTL ; 
 int ENAVAIL ; 
 int MAX_BLOCKS ; 
 scalar_t__ RESERVED_BY_OTHER (struct dpu_rm_hw_blk*,struct dpu_rm_rsvp*) ; 
 scalar_t__ _dpu_rm_get_hw_locked (struct dpu_rm*,struct dpu_rm_hw_iter*) ; 
 int /*<<< orphan*/  dpu_rm_init_hw_iter (struct dpu_rm_hw_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dpu_rm_hw_blk***,int /*<<< orphan*/ ,int) ; 
 struct dpu_hw_ctl* to_dpu_hw_ctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dpu_rm_reserve_ctls (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _dpu_rm_reserve_ctls(
		struct dpu_rm *rm,
		struct dpu_rm_rsvp *rsvp,
		const struct dpu_rm_topology_def *top)
{
	struct dpu_rm_hw_blk *ctls[MAX_BLOCKS];
	struct dpu_rm_hw_iter iter;
	int i = 0;

	memset(&ctls, 0, sizeof(ctls));

	dpu_rm_init_hw_iter(&iter, 0, DPU_HW_BLK_CTL);
	while (_dpu_rm_get_hw_locked(rm, &iter)) {
		const struct dpu_hw_ctl *ctl = to_dpu_hw_ctl(iter.blk->hw);
		unsigned long features = ctl->caps->features;
		bool has_split_display;

		if (RESERVED_BY_OTHER(iter.blk, rsvp))
			continue;

		has_split_display = BIT(DPU_CTL_SPLIT_DISPLAY) & features;

		DPU_DEBUG("ctl %d caps 0x%lX\n", iter.blk->id, features);

		if (top->needs_split_display != has_split_display)
			continue;

		ctls[i] = iter.blk;
		DPU_DEBUG("ctl %d match\n", iter.blk->id);

		if (++i == top->num_ctl)
			break;
	}

	if (i != top->num_ctl)
		return -ENAVAIL;

	for (i = 0; i < ARRAY_SIZE(ctls) && i < top->num_ctl; i++) {
		ctls[i]->rsvp_nxt = rsvp;
		trace_dpu_rm_reserve_ctls(ctls[i]->id, ctls[i]->type,
					  rsvp->enc_id);
	}

	return 0;
}