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
typedef  int /*<<< orphan*/  u64 ;
struct mm_struct {int dummy; } ;
struct cxl_context {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_fault_segment (struct cxl_context*,struct mm_struct*,int /*<<< orphan*/ ) ; 
 struct mm_struct* get_mem_context (struct cxl_context*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxl_prefault_one(struct cxl_context *ctx, u64 ea)
{
	struct mm_struct *mm;

	mm = get_mem_context(ctx);
	if (mm == NULL) {
		pr_devel("cxl_prefault_one unable to get mm %i\n",
			 pid_nr(ctx->pid));
		return;
	}

	cxl_fault_segment(ctx, mm, ea);

	mmput(mm);
}