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
typedef  size_t u32 ;
struct send_context {size_t sw_index; size_t hw_context; int /*<<< orphan*/  buffers_allocated; struct send_context* sr; int /*<<< orphan*/  halt_work; int /*<<< orphan*/  piowait; struct hfi1_devdata* dd; int /*<<< orphan*/  flags; } ;
struct hfi1_devdata {int /*<<< orphan*/  sc_lock; TYPE_1__* send_contexts; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ENABLE ; 
 int /*<<< orphan*/  CHECK_OPCODE ; 
 int /*<<< orphan*/  CHECK_PARTITION_KEY ; 
 int /*<<< orphan*/  CREDIT_CTRL ; 
 int /*<<< orphan*/  CREDIT_RETURN_ADDR ; 
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  ERR_MASK ; 
 int /*<<< orphan*/  SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCF_IN_FREE ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct send_context*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc_disable (struct send_context*) ; 
 int /*<<< orphan*/  sc_hw_free (struct hfi1_devdata*,size_t,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_kctxt_csr (struct hfi1_devdata*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sc_free(struct send_context *sc)
{
	struct hfi1_devdata *dd;
	unsigned long flags;
	u32 sw_index;
	u32 hw_context;

	if (!sc)
		return;

	sc->flags |= SCF_IN_FREE;	/* ensure no restarts */
	dd = sc->dd;
	if (!list_empty(&sc->piowait))
		dd_dev_err(dd, "piowait list not empty!\n");
	sw_index = sc->sw_index;
	hw_context = sc->hw_context;
	sc_disable(sc);	/* make sure the HW is disabled */
	flush_work(&sc->halt_work);

	spin_lock_irqsave(&dd->sc_lock, flags);
	dd->send_contexts[sw_index].sc = NULL;

	/* clear/disable all registers set in sc_alloc */
	write_kctxt_csr(dd, hw_context, SC(CTRL), 0);
	write_kctxt_csr(dd, hw_context, SC(CHECK_ENABLE), 0);
	write_kctxt_csr(dd, hw_context, SC(ERR_MASK), 0);
	write_kctxt_csr(dd, hw_context, SC(CHECK_PARTITION_KEY), 0);
	write_kctxt_csr(dd, hw_context, SC(CHECK_OPCODE), 0);
	write_kctxt_csr(dd, hw_context, SC(CREDIT_RETURN_ADDR), 0);
	write_kctxt_csr(dd, hw_context, SC(CREDIT_CTRL), 0);

	/* release the index and context for re-use */
	sc_hw_free(dd, sw_index, hw_context);
	spin_unlock_irqrestore(&dd->sc_lock, flags);

	kfree(sc->sr);
	free_percpu(sc->buffers_allocated);
	kfree(sc);
}