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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct spa {int /*<<< orphan*/  spa_lock; struct ocxl_process_element* spa_mem; int /*<<< orphan*/  pe_tree; } ;
struct pe_data {void (* xsl_err_cb ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;void* xsl_err_data; struct mm_struct* mm; } ;
struct ocxl_process_element {void* software_state; void* amr; void* tid; void* pid; void* lpid; void* config_state; } ;
struct ocxl_link {struct spa* spa; } ;
struct mm_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SPA_PASID_MAX ; 
 int SPA_PE_MASK ; 
 int /*<<< orphan*/  SPA_PE_VALID ; 
 int /*<<< orphan*/  SPRN_LPID ; 
 int /*<<< orphan*/  calculate_cfg_state (int) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 struct pe_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memset (struct ocxl_process_element*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_context_add_copro (struct mm_struct*) ; 
 int /*<<< orphan*/  mmgrab (struct mm_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,int,struct pe_data*) ; 
 int /*<<< orphan*/  trace_ocxl_context_add (int /*<<< orphan*/ ,struct ocxl_process_element*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ocxl_link_add_pe(void *link_handle, int pasid, u32 pidr, u32 tidr,
		u64 amr, struct mm_struct *mm,
		void (*xsl_err_cb)(void *data, u64 addr, u64 dsisr),
		void *xsl_err_data)
{
	struct ocxl_link *link = (struct ocxl_link *) link_handle;
	struct spa *spa = link->spa;
	struct ocxl_process_element *pe;
	int pe_handle, rc = 0;
	struct pe_data *pe_data;

	BUILD_BUG_ON(sizeof(struct ocxl_process_element) != 128);
	if (pasid > SPA_PASID_MAX)
		return -EINVAL;

	mutex_lock(&spa->spa_lock);
	pe_handle = pasid & SPA_PE_MASK;
	pe = spa->spa_mem + pe_handle;

	if (pe->software_state) {
		rc = -EBUSY;
		goto unlock;
	}

	pe_data = kmalloc(sizeof(*pe_data), GFP_KERNEL);
	if (!pe_data) {
		rc = -ENOMEM;
		goto unlock;
	}

	pe_data->mm = mm;
	pe_data->xsl_err_cb = xsl_err_cb;
	pe_data->xsl_err_data = xsl_err_data;

	memset(pe, 0, sizeof(struct ocxl_process_element));
	pe->config_state = cpu_to_be64(calculate_cfg_state(pidr == 0));
	pe->lpid = cpu_to_be32(mfspr(SPRN_LPID));
	pe->pid = cpu_to_be32(pidr);
	pe->tid = cpu_to_be32(tidr);
	pe->amr = cpu_to_be64(amr);
	pe->software_state = cpu_to_be32(SPA_PE_VALID);

	/*
	 * For user contexts, register a copro so that TLBIs are seen
	 * by the nest MMU. If we have a kernel context, TLBIs are
	 * already global.
	 */
	if (mm)
		mm_context_add_copro(mm);
	/*
	 * Barrier is to make sure PE is visible in the SPA before it
	 * is used by the device. It also helps with the global TLBI
	 * invalidation
	 */
	mb();
	radix_tree_insert(&spa->pe_tree, pe_handle, pe_data);

	/*
	 * The mm must stay valid for as long as the device uses it. We
	 * lower the count when the context is removed from the SPA.
	 *
	 * We grab mm_count (and not mm_users), as we don't want to
	 * end up in a circular dependency if a process mmaps its
	 * mmio, therefore incrementing the file ref count when
	 * calling mmap(), and forgets to unmap before exiting. In
	 * that scenario, when the kernel handles the death of the
	 * process, the file is not cleaned because unmap was not
	 * called, and the mm wouldn't be freed because we would still
	 * have a reference on mm_users. Incrementing mm_count solves
	 * the problem.
	 */
	if (mm)
		mmgrab(mm);
	trace_ocxl_context_add(current->pid, spa->spa_mem, pasid, pidr, tidr);
unlock:
	mutex_unlock(&spa->spa_lock);
	return rc;
}