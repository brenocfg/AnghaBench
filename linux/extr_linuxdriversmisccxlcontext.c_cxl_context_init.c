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
struct TYPE_3__ {scalar_t__* range; } ;
struct cxl_context {int master; int assign_tidr; int pending_irq; int pending_fault; int pending_afu_err; int pe; int external_pe; int pe_inserted; struct cxl_afu* afu; int /*<<< orphan*/ * elem; int /*<<< orphan*/  status; int /*<<< orphan*/  status_mutex; TYPE_1__ irqs; int /*<<< orphan*/  irq_names; int /*<<< orphan*/ * irq_bitmap; int /*<<< orphan*/  lock; int /*<<< orphan*/  wq; int /*<<< orphan*/  fault_work; int /*<<< orphan*/  sste_lock; scalar_t__ tidr; int /*<<< orphan*/ * mapping; int /*<<< orphan*/  mapping_lock; int /*<<< orphan*/ * pid; } ;
struct cxl_afu {TYPE_2__* native; int /*<<< orphan*/  contexts_lock; int /*<<< orphan*/  num_procs; int /*<<< orphan*/  contexts_idr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int CXL_IRQ_RANGES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENED ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_afu_get (struct cxl_afu*) ; 
 int cxl_alloc_sst (struct cxl_context*) ; 
 int /*<<< orphan*/  cxl_handle_fault ; 
 scalar_t__ cxl_is_power8 () ; 
 int idr_alloc (int /*<<< orphan*/ *,struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int cxl_context_init(struct cxl_context *ctx, struct cxl_afu *afu, bool master)
{
	int i;

	ctx->afu = afu;
	ctx->master = master;
	ctx->pid = NULL; /* Set in start work ioctl */
	mutex_init(&ctx->mapping_lock);
	ctx->mapping = NULL;
	ctx->tidr = 0;
	ctx->assign_tidr = false;

	if (cxl_is_power8()) {
		spin_lock_init(&ctx->sste_lock);

		/*
		 * Allocate the segment table before we put it in the IDR so that we
		 * can always access it when dereferenced from IDR. For the same
		 * reason, the segment table is only destroyed after the context is
		 * removed from the IDR.  Access to this in the IOCTL is protected by
		 * Linux filesytem symantics (can't IOCTL until open is complete).
		 */
		i = cxl_alloc_sst(ctx);
		if (i)
			return i;
	}

	INIT_WORK(&ctx->fault_work, cxl_handle_fault);

	init_waitqueue_head(&ctx->wq);
	spin_lock_init(&ctx->lock);

	ctx->irq_bitmap = NULL;
	ctx->pending_irq = false;
	ctx->pending_fault = false;
	ctx->pending_afu_err = false;

	INIT_LIST_HEAD(&ctx->irq_names);

	/*
	 * When we have to destroy all contexts in cxl_context_detach_all() we
	 * end up with afu_release_irqs() called from inside a
	 * idr_for_each_entry(). Hence we need to make sure that anything
	 * dereferenced from this IDR is ok before we allocate the IDR here.
	 * This clears out the IRQ ranges to ensure this.
	 */
	for (i = 0; i < CXL_IRQ_RANGES; i++)
		ctx->irqs.range[i] = 0;

	mutex_init(&ctx->status_mutex);

	ctx->status = OPENED;

	/*
	 * Allocating IDR! We better make sure everything's setup that
	 * dereferences from it.
	 */
	mutex_lock(&afu->contexts_lock);
	idr_preload(GFP_KERNEL);
	i = idr_alloc(&ctx->afu->contexts_idr, ctx, 0,
		      ctx->afu->num_procs, GFP_NOWAIT);
	idr_preload_end();
	mutex_unlock(&afu->contexts_lock);
	if (i < 0)
		return i;

	ctx->pe = i;
	if (cpu_has_feature(CPU_FTR_HVMODE)) {
		ctx->elem = &ctx->afu->native->spa[i];
		ctx->external_pe = ctx->pe;
	} else {
		ctx->external_pe = -1; /* assigned when attaching */
	}
	ctx->pe_inserted = false;

	/*
	 * take a ref on the afu so that it stays alive at-least till
	 * this context is reclaimed inside reclaim_ctx.
	 */
	cxl_afu_get(afu);
	return 0;
}