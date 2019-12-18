#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct pe_data {TYPE_3__* mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  fault_work; struct pe_data pe_data; scalar_t__ dsisr; scalar_t__ dar; scalar_t__ pe; } ;
struct spa {TYPE_2__ xsl_fault; int /*<<< orphan*/  pe_tree; struct ocxl_process_element* spa_mem; } ;
struct ocxl_process_element {int /*<<< orphan*/  pid; } ;
struct ocxl_link {struct spa* spa; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int id; } ;
struct TYPE_6__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_ERROR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SPA_PE_MASK ; 
 scalar_t__ SPA_XSL_TF ; 
 int /*<<< orphan*/  WARN (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ack_irq (struct spa*,int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ mmget_not_zero (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 struct pe_data* radix_tree_lookup (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_irq (struct spa*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocxl_fault (struct ocxl_process_element*,scalar_t__,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static irqreturn_t xsl_fault_handler(int irq, void *data)
{
	struct ocxl_link *link = (struct ocxl_link *) data;
	struct spa *spa = link->spa;
	u64 dsisr, dar, pe_handle;
	struct pe_data *pe_data;
	struct ocxl_process_element *pe;
	int pid;
	bool schedule = false;

	read_irq(spa, &dsisr, &dar, &pe_handle);
	trace_ocxl_fault(spa->spa_mem, pe_handle, dsisr, dar, -1);

	WARN_ON(pe_handle > SPA_PE_MASK);
	pe = spa->spa_mem + pe_handle;
	pid = be32_to_cpu(pe->pid);
	/* We could be reading all null values here if the PE is being
	 * removed while an interrupt kicks in. It's not supposed to
	 * happen if the driver notified the AFU to terminate the
	 * PASID, and the AFU waited for pending operations before
	 * acknowledging. But even if it happens, we won't find a
	 * memory context below and fail silently, so it should be ok.
	 */
	if (!(dsisr & SPA_XSL_TF)) {
		WARN(1, "Invalid xsl interrupt fault register %#llx\n", dsisr);
		ack_irq(spa, ADDRESS_ERROR);
		return IRQ_HANDLED;
	}

	rcu_read_lock();
	pe_data = radix_tree_lookup(&spa->pe_tree, pe_handle);
	if (!pe_data) {
		/*
		 * Could only happen if the driver didn't notify the
		 * AFU about PASID termination before removing the PE,
		 * or the AFU didn't wait for all memory access to
		 * have completed.
		 *
		 * Either way, we fail early, but we shouldn't log an
		 * error message, as it is a valid (if unexpected)
		 * scenario
		 */
		rcu_read_unlock();
		pr_debug("Unknown mm context for xsl interrupt\n");
		ack_irq(spa, ADDRESS_ERROR);
		return IRQ_HANDLED;
	}

	if (!pe_data->mm) {
		/*
		 * translation fault from a kernel context - an OpenCAPI
		 * device tried to access a bad kernel address
		 */
		rcu_read_unlock();
		pr_warn("Unresolved OpenCAPI xsl fault in kernel context\n");
		ack_irq(spa, ADDRESS_ERROR);
		return IRQ_HANDLED;
	}
	WARN_ON(pe_data->mm->context.id != pid);

	if (mmget_not_zero(pe_data->mm)) {
			spa->xsl_fault.pe = pe_handle;
			spa->xsl_fault.dar = dar;
			spa->xsl_fault.dsisr = dsisr;
			spa->xsl_fault.pe_data = *pe_data;
			schedule = true;
			/* mm_users count released by bottom half */
	}
	rcu_read_unlock();
	if (schedule)
		schedule_work(&spa->xsl_fault.fault_work);
	else
		ack_irq(spa, ADDRESS_ERROR);
	return IRQ_HANDLED;
}