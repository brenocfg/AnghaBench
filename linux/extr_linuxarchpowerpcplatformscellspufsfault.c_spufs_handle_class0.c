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
struct TYPE_2__ {unsigned long class_0_pending; int /*<<< orphan*/  class_0_dar; } ;
struct spu_context {TYPE_1__ csa; } ;

/* Variables and functions */
 unsigned long CLASS0_DMA_ALIGNMENT_INTR ; 
 unsigned long CLASS0_INTR_MASK ; 
 unsigned long CLASS0_INVALID_DMA_COMMAND_INTR ; 
 unsigned long CLASS0_SPU_ERROR_INTR ; 
 int EIO ; 
 int /*<<< orphan*/  SPE_EVENT_DMA_ALIGNMENT ; 
 int /*<<< orphan*/  SPE_EVENT_INVALID_DMA ; 
 int /*<<< orphan*/  SPE_EVENT_SPE_ERROR ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spufs_handle_event (struct spu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int spufs_handle_class0(struct spu_context *ctx)
{
	unsigned long stat = ctx->csa.class_0_pending & CLASS0_INTR_MASK;

	if (likely(!stat))
		return 0;

	if (stat & CLASS0_DMA_ALIGNMENT_INTR)
		spufs_handle_event(ctx, ctx->csa.class_0_dar,
			SPE_EVENT_DMA_ALIGNMENT);

	if (stat & CLASS0_INVALID_DMA_COMMAND_INTR)
		spufs_handle_event(ctx, ctx->csa.class_0_dar,
			SPE_EVENT_INVALID_DMA);

	if (stat & CLASS0_SPU_ERROR_INTR)
		spufs_handle_event(ctx, ctx->csa.class_0_dar,
			SPE_EVENT_SPE_ERROR);

	ctx->csa.class_0_pending = 0;

	return -EIO;
}