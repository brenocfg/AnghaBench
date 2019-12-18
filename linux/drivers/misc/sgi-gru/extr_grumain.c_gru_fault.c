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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {unsigned long address; struct vm_area_struct* vma; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; } ;
struct gru_thread_state {unsigned long ts_steal_jiffies; int /*<<< orphan*/  ts_ctxlock; int /*<<< orphan*/  ts_ctxnum; int /*<<< orphan*/  ts_gru; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRU_ASSIGN_DELAY ; 
 int GRU_GSEG_PAGESIZE ; 
 unsigned long GRU_STEAL_DELAY ; 
 int /*<<< orphan*/  GSEG_BASE (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TSID (unsigned long,struct vm_area_struct*) ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  gru_assign_gru_context (struct gru_thread_state*) ; 
 int /*<<< orphan*/  gru_check_context_placement (struct gru_thread_state*) ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 struct gru_thread_state* gru_find_thread_state (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_load_context (struct gru_thread_state*) ; 
 int /*<<< orphan*/  gru_steal_context (struct gru_thread_state*) ; 
 int /*<<< orphan*/  grudev ; 
 unsigned long gseg_physical_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  load_user_context ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nopfn ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,int /*<<< orphan*/ ) ; 

vm_fault_t gru_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct gru_thread_state *gts;
	unsigned long paddr, vaddr;
	unsigned long expires;

	vaddr = vmf->address;
	gru_dbg(grudev, "vma %p, vaddr 0x%lx (0x%lx)\n",
		vma, vaddr, GSEG_BASE(vaddr));
	STAT(nopfn);

	/* The following check ensures vaddr is a valid address in the VMA */
	gts = gru_find_thread_state(vma, TSID(vaddr, vma));
	if (!gts)
		return VM_FAULT_SIGBUS;

again:
	mutex_lock(&gts->ts_ctxlock);
	preempt_disable();

	gru_check_context_placement(gts);

	if (!gts->ts_gru) {
		STAT(load_user_context);
		if (!gru_assign_gru_context(gts)) {
			preempt_enable();
			mutex_unlock(&gts->ts_ctxlock);
			set_current_state(TASK_INTERRUPTIBLE);
			schedule_timeout(GRU_ASSIGN_DELAY);  /* true hack ZZZ */
			expires = gts->ts_steal_jiffies + GRU_STEAL_DELAY;
			if (time_before(expires, jiffies))
				gru_steal_context(gts);
			goto again;
		}
		gru_load_context(gts);
		paddr = gseg_physical_address(gts->ts_gru, gts->ts_ctxnum);
		remap_pfn_range(vma, vaddr & ~(GRU_GSEG_PAGESIZE - 1),
				paddr >> PAGE_SHIFT, GRU_GSEG_PAGESIZE,
				vma->vm_page_prot);
	}

	preempt_enable();
	mutex_unlock(&gts->ts_ctxlock);

	return VM_FAULT_NOPAGE;
}