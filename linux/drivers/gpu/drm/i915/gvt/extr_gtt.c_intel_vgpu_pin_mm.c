#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lru_list; } ;
struct intel_vgpu_mm {scalar_t__ type; TYPE_3__* vgpu; TYPE_1__ ppgtt_mm; int /*<<< orphan*/  pincount; } ;
struct TYPE_8__ {int /*<<< orphan*/  ppgtt_mm_lock; int /*<<< orphan*/  ppgtt_mm_lru_list_head; } ;
struct TYPE_7__ {TYPE_2__* gvt; } ;
struct TYPE_6__ {TYPE_4__ gtt; } ;

/* Variables and functions */
 scalar_t__ INTEL_GVT_MM_PPGTT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int shadow_ppgtt_mm (struct intel_vgpu_mm*) ; 

int intel_vgpu_pin_mm(struct intel_vgpu_mm *mm)
{
	int ret;

	atomic_inc(&mm->pincount);

	if (mm->type == INTEL_GVT_MM_PPGTT) {
		ret = shadow_ppgtt_mm(mm);
		if (ret)
			return ret;

		mutex_lock(&mm->vgpu->gvt->gtt.ppgtt_mm_lock);
		list_move_tail(&mm->ppgtt_mm.lru_list,
			       &mm->vgpu->gvt->gtt.ppgtt_mm_lru_list_head);
		mutex_unlock(&mm->vgpu->gvt->gtt.ppgtt_mm_lock);
	}

	return 0;
}