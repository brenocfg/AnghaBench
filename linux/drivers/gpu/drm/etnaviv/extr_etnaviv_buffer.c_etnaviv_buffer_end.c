#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct etnaviv_cmdbuf {int user_size; } ;
struct etnaviv_gpu {scalar_t__ exec_state; int /*<<< orphan*/  lock; struct etnaviv_cmdbuf buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_END (struct etnaviv_cmdbuf*) ; 
 int /*<<< orphan*/  CMD_LOAD_STATE (struct etnaviv_cmdbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMD_SEM (struct etnaviv_cmdbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_STALL (struct etnaviv_cmdbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ETNA_PIPE_2D ; 
 scalar_t__ ETNA_PIPE_3D ; 
 int /*<<< orphan*/  SYNC_RECIPIENT_FE ; 
 int /*<<< orphan*/  SYNC_RECIPIENT_PE ; 
 int /*<<< orphan*/  VIVS_GL_FLUSH_CACHE ; 
 int VIVS_GL_FLUSH_CACHE_COLOR ; 
 int VIVS_GL_FLUSH_CACHE_DEPTH ; 
 int VIVS_GL_FLUSH_CACHE_PE2D ; 
 int VIVS_GL_FLUSH_CACHE_SHADER_L2 ; 
 int VIVS_GL_FLUSH_CACHE_TEXTURE ; 
 int VIVS_GL_FLUSH_CACHE_TEXTUREVS ; 
 int /*<<< orphan*/  VIVS_TS_FLUSH_CACHE ; 
 int VIVS_TS_FLUSH_CACHE_FLUSH ; 
 int VIV_FE_END_HEADER_OP_END ; 
 int VIV_FE_LINK_HEADER_OP_LINK ; 
 int VIV_FE_LINK_HEADER_PREFETCH (unsigned int) ; 
 int /*<<< orphan*/  etnaviv_buffer_replace_wait (struct etnaviv_cmdbuf*,unsigned int,int,int) ; 
 int etnaviv_buffer_reserve (struct etnaviv_gpu*,struct etnaviv_cmdbuf*,unsigned int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void etnaviv_buffer_end(struct etnaviv_gpu *gpu)
{
	struct etnaviv_cmdbuf *buffer = &gpu->buffer;
	unsigned int waitlink_offset = buffer->user_size - 16;
	u32 link_target, flush = 0;

	lockdep_assert_held(&gpu->lock);

	if (gpu->exec_state == ETNA_PIPE_2D)
		flush = VIVS_GL_FLUSH_CACHE_PE2D;
	else if (gpu->exec_state == ETNA_PIPE_3D)
		flush = VIVS_GL_FLUSH_CACHE_DEPTH |
			VIVS_GL_FLUSH_CACHE_COLOR |
			VIVS_GL_FLUSH_CACHE_TEXTURE |
			VIVS_GL_FLUSH_CACHE_TEXTUREVS |
			VIVS_GL_FLUSH_CACHE_SHADER_L2;

	if (flush) {
		unsigned int dwords = 7;

		link_target = etnaviv_buffer_reserve(gpu, buffer, dwords);

		CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
		CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
		CMD_LOAD_STATE(buffer, VIVS_GL_FLUSH_CACHE, flush);
		if (gpu->exec_state == ETNA_PIPE_3D)
			CMD_LOAD_STATE(buffer, VIVS_TS_FLUSH_CACHE,
				       VIVS_TS_FLUSH_CACHE_FLUSH);
		CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
		CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
		CMD_END(buffer);

		etnaviv_buffer_replace_wait(buffer, waitlink_offset,
					    VIV_FE_LINK_HEADER_OP_LINK |
					    VIV_FE_LINK_HEADER_PREFETCH(dwords),
					    link_target);
	} else {
		/* Replace the last link-wait with an "END" command */
		etnaviv_buffer_replace_wait(buffer, waitlink_offset,
					    VIV_FE_END_HEADER_OP_END, 0);
	}
}