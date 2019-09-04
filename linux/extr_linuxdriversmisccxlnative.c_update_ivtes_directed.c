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
struct TYPE_4__ {int /*<<< orphan*/ * range; int /*<<< orphan*/ * offset; } ;
struct cxl_context {scalar_t__ status; TYPE_2__ irqs; TYPE_1__* elem; } ;
struct TYPE_3__ {void** ivte_ranges; void** ivte_offsets; } ;

/* Variables and functions */
 int CXL_IRQ_RANGES ; 
 scalar_t__ STARTED ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_process_element (struct cxl_context*) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_process_element (struct cxl_context*) ; 
 int /*<<< orphan*/  terminate_process_element (struct cxl_context*) ; 

__attribute__((used)) static void update_ivtes_directed(struct cxl_context *ctx)
{
	bool need_update = (ctx->status == STARTED);
	int r;

	if (need_update) {
		WARN_ON(terminate_process_element(ctx));
		WARN_ON(remove_process_element(ctx));
	}

	for (r = 0; r < CXL_IRQ_RANGES; r++) {
		ctx->elem->ivte_offsets[r] = cpu_to_be16(ctx->irqs.offset[r]);
		ctx->elem->ivte_ranges[r] = cpu_to_be16(ctx->irqs.range[r]);
	}

	/*
	 * Theoretically we could use the update llcmd, instead of a
	 * terminate/remove/add (or if an atomic update was required we could
	 * do a suspend/update/resume), however it seems there might be issues
	 * with the update llcmd on some cards (including those using an XSL on
	 * an ASIC) so for now it's safest to go with the commands that are
	 * known to work. In the future if we come across a situation where the
	 * card may be performing transactions using the same PE while we are
	 * doing this update we might need to revisit this.
	 */
	if (need_update)
		WARN_ON(add_process_element(ctx));
}