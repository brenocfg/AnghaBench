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
struct ocxl_context {TYPE_2__* afu; scalar_t__ mapping; int /*<<< orphan*/  pasid; } ;
struct afu_irq {int /*<<< orphan*/  hw_irq; int /*<<< orphan*/  private; int /*<<< orphan*/  (* free_private ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__* fn; } ;
struct TYPE_3__ {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  kfree (struct afu_irq*) ; 
 int /*<<< orphan*/  ocxl_irq_id_to_offset (struct ocxl_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocxl_link_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_afu_irq (struct afu_irq*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocxl_afu_irq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_mapping_range (scalar_t__,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void afu_irq_free(struct afu_irq *irq, struct ocxl_context *ctx)
{
	trace_ocxl_afu_irq_free(ctx->pasid, irq->id);
	if (ctx->mapping)
		unmap_mapping_range(ctx->mapping,
				ocxl_irq_id_to_offset(ctx, irq->id),
				1 << PAGE_SHIFT, 1);
	release_afu_irq(irq);
	if (irq->free_private)
		irq->free_private(irq->private);
	ocxl_link_free_irq(ctx->afu->fn->link, irq->hw_irq);
	kfree(irq);
}