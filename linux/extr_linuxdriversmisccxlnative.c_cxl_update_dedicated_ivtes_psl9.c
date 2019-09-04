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
struct TYPE_3__ {int /*<<< orphan*/ * range; int /*<<< orphan*/ * offset; } ;
struct cxl_context {TYPE_1__ irqs; TYPE_2__* elem; } ;
struct TYPE_4__ {void** ivte_ranges; void** ivte_offsets; } ;

/* Variables and functions */
 int CXL_IRQ_RANGES ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 

void cxl_update_dedicated_ivtes_psl9(struct cxl_context *ctx)
{
	int r;

	for (r = 0; r < CXL_IRQ_RANGES; r++) {
		ctx->elem->ivte_offsets[r] = cpu_to_be16(ctx->irqs.offset[r]);
		ctx->elem->ivte_ranges[r] = cpu_to_be16(ctx->irqs.range[r]);
	}
}