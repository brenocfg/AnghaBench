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
struct msm_ringbuffer {int dummy; } ;
struct msm_gpu {TYPE_1__* dev; } ;
struct msm_gem_submit {unsigned int nr_cmds; int seqno; TYPE_2__* cmd; struct msm_ringbuffer* ring; } ;
struct msm_file_private {int dummy; } ;
struct msm_drm_private {struct msm_file_private* lastctx; } ;
struct TYPE_4__ {int type; int size; int /*<<< orphan*/  iova; } ;
struct TYPE_3__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int CACHE_FLUSH_TS ; 
 int /*<<< orphan*/  CP_EVENT_WRITE ; 
 int /*<<< orphan*/  CP_INDIRECT_BUFFER_PFE ; 
#define  MSM_SUBMIT_CMD_BUF 130 
#define  MSM_SUBMIT_CMD_CTX_RESTORE_BUF 129 
#define  MSM_SUBMIT_CMD_IB_TARGET_BUF 128 
 int /*<<< orphan*/  OUT_PKT4 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_PKT7 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (struct msm_ringbuffer*,int) ; 
 int PC_CCU_INVALIDATE_COLOR ; 
 int PC_CCU_INVALIDATE_DEPTH ; 
 int /*<<< orphan*/  REG_A6XX_CP_SCRATCH_REG (int) ; 
 int /*<<< orphan*/  a6xx_flush (struct msm_gpu*,struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  fence ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbmemptr (struct msm_ringbuffer*,int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a6xx_submit(struct msm_gpu *gpu, struct msm_gem_submit *submit,
	struct msm_file_private *ctx)
{
	struct msm_drm_private *priv = gpu->dev->dev_private;
	struct msm_ringbuffer *ring = submit->ring;
	unsigned int i;

	/* Invalidate CCU depth and color */
	OUT_PKT7(ring, CP_EVENT_WRITE, 1);
	OUT_RING(ring, PC_CCU_INVALIDATE_DEPTH);

	OUT_PKT7(ring, CP_EVENT_WRITE, 1);
	OUT_RING(ring, PC_CCU_INVALIDATE_COLOR);

	/* Submit the commands */
	for (i = 0; i < submit->nr_cmds; i++) {
		switch (submit->cmd[i].type) {
		case MSM_SUBMIT_CMD_IB_TARGET_BUF:
			break;
		case MSM_SUBMIT_CMD_CTX_RESTORE_BUF:
			if (priv->lastctx == ctx)
				break;
		case MSM_SUBMIT_CMD_BUF:
			OUT_PKT7(ring, CP_INDIRECT_BUFFER_PFE, 3);
			OUT_RING(ring, lower_32_bits(submit->cmd[i].iova));
			OUT_RING(ring, upper_32_bits(submit->cmd[i].iova));
			OUT_RING(ring, submit->cmd[i].size);
			break;
		}
	}

	/* Write the fence to the scratch register */
	OUT_PKT4(ring, REG_A6XX_CP_SCRATCH_REG(2), 1);
	OUT_RING(ring, submit->seqno);

	/*
	 * Execute a CACHE_FLUSH_TS event. This will ensure that the
	 * timestamp is written to the memory and then triggers the interrupt
	 */
	OUT_PKT7(ring, CP_EVENT_WRITE, 4);
	OUT_RING(ring, CACHE_FLUSH_TS | (1 << 31));
	OUT_RING(ring, lower_32_bits(rbmemptr(ring, fence)));
	OUT_RING(ring, upper_32_bits(rbmemptr(ring, fence)));
	OUT_RING(ring, submit->seqno);

	a6xx_flush(gpu, ring);
}