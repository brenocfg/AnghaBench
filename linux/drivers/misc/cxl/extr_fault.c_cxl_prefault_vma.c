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
typedef  scalar_t__ u64 ;
struct vm_area_struct {scalar_t__ vm_start; scalar_t__ vm_end; struct vm_area_struct* vm_next; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; struct vm_area_struct* mmap; } ;
struct cxl_context {int /*<<< orphan*/  pid; } ;
struct copro_slb {scalar_t__ esid; int /*<<< orphan*/  vsid; } ;

/* Variables and functions */
 int copro_calculate_slb (struct mm_struct*,scalar_t__,struct copro_slb*) ; 
 int /*<<< orphan*/  cxl_load_segment (struct cxl_context*,struct copro_slb*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct mm_struct* get_mem_context (struct cxl_context*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 scalar_t__ next_segment (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cxl_prefault_vma(struct cxl_context *ctx)
{
	u64 ea, last_esid = 0;
	struct copro_slb slb;
	struct vm_area_struct *vma;
	int rc;
	struct mm_struct *mm;

	mm = get_mem_context(ctx);
	if (mm == NULL) {
		pr_devel("cxl_prefault_vm unable to get mm %i\n",
			 pid_nr(ctx->pid));
		return;
	}

	down_read(&mm->mmap_sem);
	for (vma = mm->mmap; vma; vma = vma->vm_next) {
		for (ea = vma->vm_start; ea < vma->vm_end;
				ea = next_segment(ea, slb.vsid)) {
			rc = copro_calculate_slb(mm, ea, &slb);
			if (rc)
				continue;

			if (last_esid == slb.esid)
				continue;

			cxl_load_segment(ctx, &slb);
			last_esid = slb.esid;
		}
	}
	up_read(&mm->mmap_sem);

	mmput(mm);
}