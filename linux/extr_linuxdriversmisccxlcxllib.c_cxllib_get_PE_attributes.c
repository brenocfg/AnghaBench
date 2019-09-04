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
struct TYPE_4__ {scalar_t__ tidr; } ;
struct task_struct {TYPE_2__ thread; } ;
struct TYPE_3__ {scalar_t__ id; } ;
struct mm_struct {TYPE_1__ context; } ;
struct cxllib_pe_attributes {scalar_t__ tid; scalar_t__ pid; int /*<<< orphan*/  lpid; int /*<<< orphan*/  sr; } ;

/* Variables and functions */
 unsigned long CXL_REAL_MODE ; 
 unsigned long CXL_TRANSLATED_MODE ; 
 int EINVAL ; 
 int /*<<< orphan*/  SPRN_LPID ; 
 int /*<<< orphan*/  cxl_calculate_sr (int,int /*<<< orphan*/ ,int,int) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 

int cxllib_get_PE_attributes(struct task_struct *task,
			     unsigned long translation_mode,
			     struct cxllib_pe_attributes *attr)
{
	struct mm_struct *mm = NULL;

	if (translation_mode != CXL_TRANSLATED_MODE &&
		translation_mode != CXL_REAL_MODE)
		return -EINVAL;

	attr->sr = cxl_calculate_sr(false,
				task == NULL,
				translation_mode == CXL_REAL_MODE,
				true);
	attr->lpid = mfspr(SPRN_LPID);
	if (task) {
		mm = get_task_mm(task);
		if (mm == NULL)
			return -EINVAL;
		/*
		 * Caller is keeping a reference on mm_users for as long
		 * as XSL uses the memory context
		 */
		attr->pid = mm->context.id;
		mmput(mm);
		attr->tid = task->thread.tidr;
	} else {
		attr->pid = 0;
		attr->tid = 0;
	}
	return 0;
}