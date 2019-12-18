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
typedef  int u32 ;
struct etnaviv_cmdbuf {int user_size; } ;
struct etnaviv_gpu {TYPE_1__* mmu_context; int /*<<< orphan*/  lock; struct etnaviv_cmdbuf buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmdbuf_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_END (struct etnaviv_cmdbuf*) ; 
 int /*<<< orphan*/  CMD_LINK (struct etnaviv_cmdbuf*,int,scalar_t__) ; 
 int /*<<< orphan*/  CMD_LOAD_STATE (struct etnaviv_cmdbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMD_WAIT (struct etnaviv_cmdbuf*) ; 
 int /*<<< orphan*/  VIVS_GL_EVENT ; 
 int VIVS_GL_EVENT_EVENT_ID (unsigned int) ; 
 int VIVS_GL_EVENT_FROM_PE ; 
 int VIV_FE_LINK_HEADER_OP_LINK ; 
 int VIV_FE_LINK_HEADER_PREFETCH (int) ; 
 int /*<<< orphan*/  etnaviv_buffer_replace_wait (struct etnaviv_cmdbuf*,unsigned int,int,int) ; 
 int etnaviv_buffer_reserve (struct etnaviv_gpu*,struct etnaviv_cmdbuf*,int) ; 
 scalar_t__ etnaviv_cmdbuf_get_va (struct etnaviv_cmdbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void etnaviv_sync_point_queue(struct etnaviv_gpu *gpu, unsigned int event)
{
	struct etnaviv_cmdbuf *buffer = &gpu->buffer;
	unsigned int waitlink_offset = buffer->user_size - 16;
	u32 dwords, target;

	lockdep_assert_held(&gpu->lock);

	/*
	 * We need at most 3 dwords in the return target:
	 * 1 event + 1 end + 1 wait + 1 link.
	 */
	dwords = 4;
	target = etnaviv_buffer_reserve(gpu, buffer, dwords);

	/* Signal sync point event */
	CMD_LOAD_STATE(buffer, VIVS_GL_EVENT, VIVS_GL_EVENT_EVENT_ID(event) |
		       VIVS_GL_EVENT_FROM_PE);

	/* Stop the FE to 'pause' the GPU */
	CMD_END(buffer);

	/* Append waitlink */
	CMD_WAIT(buffer);
	CMD_LINK(buffer, 2,
		 etnaviv_cmdbuf_get_va(buffer, &gpu->mmu_context->cmdbuf_mapping)
		 + buffer->user_size - 4);

	/*
	 * Kick off the 'sync point' command by replacing the previous
	 * WAIT with a link to the address in the ring buffer.
	 */
	etnaviv_buffer_replace_wait(buffer, waitlink_offset,
				    VIV_FE_LINK_HEADER_OP_LINK |
				    VIV_FE_LINK_HEADER_PREFETCH(dwords),
				    target);
}