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
struct etnaviv_iommu_context {int /*<<< orphan*/  cmdbuf_mapping; TYPE_1__* global; int /*<<< orphan*/  flush_seq; } ;
struct etnaviv_cmdbuf {int user_size; int size; unsigned int vaddr; } ;
struct etnaviv_gpu {int exec_state; unsigned int flush_seq; scalar_t__ sec_mode; struct etnaviv_iommu_context* mmu_context; int /*<<< orphan*/  lock; struct etnaviv_cmdbuf buffer; } ;
struct TYPE_2__ {scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_LINK (struct etnaviv_cmdbuf*,int,int) ; 
 int /*<<< orphan*/  CMD_LOAD_STATE (struct etnaviv_cmdbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMD_SEM (struct etnaviv_cmdbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_STALL (struct etnaviv_cmdbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_WAIT (struct etnaviv_cmdbuf*) ; 
 int DRM_UT_DRIVER ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 scalar_t__ ETNAVIV_IOMMU_V1 ; 
 scalar_t__ ETNA_PIPE_2D ; 
 scalar_t__ ETNA_SEC_KERNEL ; 
 scalar_t__ ETNA_SEC_NONE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNC_RECIPIENT_FE ; 
 int /*<<< orphan*/  SYNC_RECIPIENT_PE ; 
 int /*<<< orphan*/  VIVS_GL_EVENT ; 
 int VIVS_GL_EVENT_EVENT_ID (unsigned int) ; 
 int VIVS_GL_EVENT_FROM_PE ; 
 int /*<<< orphan*/  VIVS_GL_FLUSH_CACHE ; 
 int VIVS_GL_FLUSH_CACHE_COLOR ; 
 int VIVS_GL_FLUSH_CACHE_DEPTH ; 
 int VIVS_GL_FLUSH_CACHE_PE2D ; 
 int /*<<< orphan*/  VIVS_GL_FLUSH_MMU ; 
 int VIVS_GL_FLUSH_MMU_FLUSH_FEMMU ; 
 int VIVS_GL_FLUSH_MMU_FLUSH_PEMMU ; 
 int VIVS_GL_FLUSH_MMU_FLUSH_UNK1 ; 
 int VIVS_GL_FLUSH_MMU_FLUSH_UNK2 ; 
 int VIVS_GL_FLUSH_MMU_FLUSH_UNK4 ; 
 int /*<<< orphan*/  VIVS_MMUv2_CONFIGURATION ; 
 int VIVS_MMUv2_CONFIGURATION_FLUSH_FLUSH ; 
 int VIVS_MMUv2_CONFIGURATION_MODE_MASK ; 
 int /*<<< orphan*/  VIVS_MMUv2_PTA_CONFIG ; 
 int VIVS_MMUv2_PTA_CONFIG_INDEX (unsigned short) ; 
 int /*<<< orphan*/  VIVS_TS_FLUSH_CACHE ; 
 int VIVS_TS_FLUSH_CACHE_FLUSH ; 
 int VIV_FE_LINK_HEADER_OP_LINK ; 
 int VIV_FE_LINK_HEADER_PREFETCH (int) ; 
 int drm_debug ; 
 int /*<<< orphan*/  etnaviv_buffer_dump (struct etnaviv_gpu*,struct etnaviv_cmdbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  etnaviv_buffer_replace_wait (struct etnaviv_cmdbuf*,unsigned int,int,int) ; 
 int etnaviv_buffer_reserve (struct etnaviv_gpu*,struct etnaviv_cmdbuf*,int) ; 
 int /*<<< orphan*/  etnaviv_cmd_select_pipe (struct etnaviv_gpu*,struct etnaviv_cmdbuf*,int) ; 
 int etnaviv_cmdbuf_get_va (struct etnaviv_cmdbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etnaviv_iommu_context_get (struct etnaviv_iommu_context*) ; 
 int /*<<< orphan*/  etnaviv_iommu_context_put (struct etnaviv_iommu_context*) ; 
 int etnaviv_iommuv2_get_mtlb_addr (struct etnaviv_iommu_context*) ; 
 unsigned short etnaviv_iommuv2_get_pta_id (struct etnaviv_iommu_context*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,...) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,unsigned int,int,int /*<<< orphan*/ ) ; 

void etnaviv_buffer_queue(struct etnaviv_gpu *gpu, u32 exec_state,
	struct etnaviv_iommu_context *mmu_context, unsigned int event,
	struct etnaviv_cmdbuf *cmdbuf)
{
	struct etnaviv_cmdbuf *buffer = &gpu->buffer;
	unsigned int waitlink_offset = buffer->user_size - 16;
	u32 return_target, return_dwords;
	u32 link_target, link_dwords;
	bool switch_context = gpu->exec_state != exec_state;
	bool switch_mmu_context = gpu->mmu_context != mmu_context;
	unsigned int new_flush_seq = READ_ONCE(gpu->mmu_context->flush_seq);
	bool need_flush = switch_mmu_context || gpu->flush_seq != new_flush_seq;

	lockdep_assert_held(&gpu->lock);

	if (drm_debug & DRM_UT_DRIVER)
		etnaviv_buffer_dump(gpu, buffer, 0, 0x50);

	link_target = etnaviv_cmdbuf_get_va(cmdbuf,
					    &gpu->mmu_context->cmdbuf_mapping);
	link_dwords = cmdbuf->size / 8;

	/*
	 * If we need maintenance prior to submitting this buffer, we will
	 * need to append a mmu flush load state, followed by a new
	 * link to this buffer - a total of four additional words.
	 */
	if (need_flush || switch_context) {
		u32 target, extra_dwords;

		/* link command */
		extra_dwords = 1;

		/* flush command */
		if (need_flush) {
			if (gpu->mmu_context->global->version == ETNAVIV_IOMMU_V1)
				extra_dwords += 1;
			else
				extra_dwords += 3;
		}

		/* pipe switch commands */
		if (switch_context)
			extra_dwords += 4;

		/* PTA load command */
		if (switch_mmu_context && gpu->sec_mode == ETNA_SEC_KERNEL)
			extra_dwords += 1;

		target = etnaviv_buffer_reserve(gpu, buffer, extra_dwords);
		/*
		 * Switch MMU context if necessary. Must be done after the
		 * link target has been calculated, as the jump forward in the
		 * kernel ring still uses the last active MMU context before
		 * the switch.
		 */
		if (switch_mmu_context) {
			struct etnaviv_iommu_context *old_context = gpu->mmu_context;

			etnaviv_iommu_context_get(mmu_context);
			gpu->mmu_context = mmu_context;
			etnaviv_iommu_context_put(old_context);
		}

		if (need_flush) {
			/* Add the MMU flush */
			if (gpu->mmu_context->global->version == ETNAVIV_IOMMU_V1) {
				CMD_LOAD_STATE(buffer, VIVS_GL_FLUSH_MMU,
					       VIVS_GL_FLUSH_MMU_FLUSH_FEMMU |
					       VIVS_GL_FLUSH_MMU_FLUSH_UNK1 |
					       VIVS_GL_FLUSH_MMU_FLUSH_UNK2 |
					       VIVS_GL_FLUSH_MMU_FLUSH_PEMMU |
					       VIVS_GL_FLUSH_MMU_FLUSH_UNK4);
			} else {
				u32 flush = VIVS_MMUv2_CONFIGURATION_MODE_MASK |
					    VIVS_MMUv2_CONFIGURATION_FLUSH_FLUSH;

				if (switch_mmu_context &&
				    gpu->sec_mode == ETNA_SEC_KERNEL) {
					unsigned short id =
						etnaviv_iommuv2_get_pta_id(gpu->mmu_context);
					CMD_LOAD_STATE(buffer,
						VIVS_MMUv2_PTA_CONFIG,
						VIVS_MMUv2_PTA_CONFIG_INDEX(id));
				}

				if (gpu->sec_mode == ETNA_SEC_NONE)
					flush |= etnaviv_iommuv2_get_mtlb_addr(gpu->mmu_context);

				CMD_LOAD_STATE(buffer, VIVS_MMUv2_CONFIGURATION,
					       flush);
				CMD_SEM(buffer, SYNC_RECIPIENT_FE,
					SYNC_RECIPIENT_PE);
				CMD_STALL(buffer, SYNC_RECIPIENT_FE,
					SYNC_RECIPIENT_PE);
			}

			gpu->flush_seq = new_flush_seq;
		}

		if (switch_context) {
			etnaviv_cmd_select_pipe(gpu, buffer, exec_state);
			gpu->exec_state = exec_state;
		}

		/* And the link to the submitted buffer */
		link_target = etnaviv_cmdbuf_get_va(cmdbuf,
					&gpu->mmu_context->cmdbuf_mapping);
		CMD_LINK(buffer, link_dwords, link_target);

		/* Update the link target to point to above instructions */
		link_target = target;
		link_dwords = extra_dwords;
	}

	/*
	 * Append a LINK to the submitted command buffer to return to
	 * the ring buffer.  return_target is the ring target address.
	 * We need at most 7 dwords in the return target: 2 cache flush +
	 * 2 semaphore stall + 1 event + 1 wait + 1 link.
	 */
	return_dwords = 7;
	return_target = etnaviv_buffer_reserve(gpu, buffer, return_dwords);
	CMD_LINK(cmdbuf, return_dwords, return_target);

	/*
	 * Append a cache flush, stall, event, wait and link pointing back to
	 * the wait command to the ring buffer.
	 */
	if (gpu->exec_state == ETNA_PIPE_2D) {
		CMD_LOAD_STATE(buffer, VIVS_GL_FLUSH_CACHE,
				       VIVS_GL_FLUSH_CACHE_PE2D);
	} else {
		CMD_LOAD_STATE(buffer, VIVS_GL_FLUSH_CACHE,
				       VIVS_GL_FLUSH_CACHE_DEPTH |
				       VIVS_GL_FLUSH_CACHE_COLOR);
		CMD_LOAD_STATE(buffer, VIVS_TS_FLUSH_CACHE,
				       VIVS_TS_FLUSH_CACHE_FLUSH);
	}
	CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
	CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
	CMD_LOAD_STATE(buffer, VIVS_GL_EVENT, VIVS_GL_EVENT_EVENT_ID(event) |
		       VIVS_GL_EVENT_FROM_PE);
	CMD_WAIT(buffer);
	CMD_LINK(buffer, 2,
		 etnaviv_cmdbuf_get_va(buffer, &gpu->mmu_context->cmdbuf_mapping)
		 + buffer->user_size - 4);

	if (drm_debug & DRM_UT_DRIVER)
		pr_info("stream link to 0x%08x @ 0x%08x %p\n",
			return_target,
			etnaviv_cmdbuf_get_va(cmdbuf, &gpu->mmu_context->cmdbuf_mapping),
			cmdbuf->vaddr);

	if (drm_debug & DRM_UT_DRIVER) {
		print_hex_dump(KERN_INFO, "cmd ", DUMP_PREFIX_OFFSET, 16, 4,
			       cmdbuf->vaddr, cmdbuf->size, 0);

		pr_info("link op: %p\n", buffer->vaddr + waitlink_offset);
		pr_info("addr: 0x%08x\n", link_target);
		pr_info("back: 0x%08x\n", return_target);
		pr_info("event: %d\n", event);
	}

	/*
	 * Kick off the submitted command by replacing the previous
	 * WAIT with a link to the address in the ring buffer.
	 */
	etnaviv_buffer_replace_wait(buffer, waitlink_offset,
				    VIV_FE_LINK_HEADER_OP_LINK |
				    VIV_FE_LINK_HEADER_PREFETCH(link_dwords),
				    link_target);

	if (drm_debug & DRM_UT_DRIVER)
		etnaviv_buffer_dump(gpu, buffer, 0, 0x50);
}