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
struct ar_context {TYPE_2__* ohci; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ card; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  ar_buffer_bus (struct ar_context*,unsigned int) ; 
 unsigned int ar_first_buffer_index (struct ar_context*) ; 
 unsigned int ar_next_buffer_index (unsigned int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar_sync_buffers_for_cpu(struct ar_context *ctx,
				    unsigned int end_buffer_index,
				    unsigned int end_buffer_offset)
{
	unsigned int i;

	i = ar_first_buffer_index(ctx);
	while (i != end_buffer_index) {
		dma_sync_single_for_cpu(ctx->ohci->card.device,
					ar_buffer_bus(ctx, i),
					PAGE_SIZE, DMA_FROM_DEVICE);
		i = ar_next_buffer_index(i);
	}
	if (end_buffer_offset > 0)
		dma_sync_single_for_cpu(ctx->ohci->card.device,
					ar_buffer_bus(ctx, i),
					end_buffer_offset, DMA_FROM_DEVICE);
}