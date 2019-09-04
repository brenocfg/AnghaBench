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
struct cxl_context {TYPE_1__* afu; int /*<<< orphan*/  irqs; } ;
typedef  scalar_t__ irq_hw_number_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* release_irq_ranges ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int /*<<< orphan*/  afu_irq_name_free (struct cxl_context*) ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ cxl_find_afu_irq (struct cxl_context*,int /*<<< orphan*/ ) ; 
 TYPE_2__* cxl_ops ; 
 int /*<<< orphan*/  cxl_unmap_irq (unsigned int,struct cxl_context*) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cxl_free_afu_irqs(struct cxl_context *ctx)
{
	irq_hw_number_t hwirq;
	unsigned int virq;

	if (!cpu_has_feature(CPU_FTR_HVMODE)) {
		hwirq = cxl_find_afu_irq(ctx, 0);
		if (hwirq) {
			virq = irq_find_mapping(NULL, hwirq);
			if (virq)
				cxl_unmap_irq(virq, ctx);
		}
	}
	afu_irq_name_free(ctx);
	cxl_ops->release_irq_ranges(&ctx->irqs, ctx->afu->adapter);
}