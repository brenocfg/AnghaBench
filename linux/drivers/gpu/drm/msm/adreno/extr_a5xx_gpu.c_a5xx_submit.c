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
struct msm_ringbuffer {size_t id; } ;
struct msm_gpu {TYPE_1__* dev; } ;
struct msm_gem_submit {unsigned int nr_cmds; int seqno; TYPE_2__* cmd; struct msm_ringbuffer* ring; scalar_t__ in_rb; } ;
struct msm_file_private {int dummy; } ;
struct msm_drm_private {struct msm_file_private* lastctx; } ;
struct adreno_gpu {int dummy; } ;
struct a5xx_gpu {int /*<<< orphan*/ * preempt_iova; } ;
struct TYPE_4__ {int type; int size; int /*<<< orphan*/  iova; } ;
struct TYPE_3__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int CACHE_FLUSH_TS ; 
 int /*<<< orphan*/  CONFIG_DRM_MSM_GPU_SUDO ; 
 int /*<<< orphan*/  CP_CONTEXT_SWITCH_YIELD ; 
 int /*<<< orphan*/  CP_EVENT_WRITE ; 
 int /*<<< orphan*/  CP_INDIRECT_BUFFER_PFE ; 
 int /*<<< orphan*/  CP_PREEMPT_ENABLE_GLOBAL ; 
 int /*<<< orphan*/  CP_SET_PROTECTED_MODE ; 
 int /*<<< orphan*/  CP_SET_RENDER_MODE ; 
 int /*<<< orphan*/  CP_YIELD_ENABLE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
#define  MSM_SUBMIT_CMD_BUF 130 
#define  MSM_SUBMIT_CMD_CTX_RESTORE_BUF 129 
#define  MSM_SUBMIT_CMD_IB_TARGET_BUF 128 
 int /*<<< orphan*/  OUT_PKT4 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_PKT7 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (struct msm_ringbuffer*,int) ; 
 int /*<<< orphan*/  REG_A5XX_CP_CONTEXT_SWITCH_SAVE_ADDR_LO ; 
 int /*<<< orphan*/  REG_A5XX_CP_SCRATCH_REG (int) ; 
 int /*<<< orphan*/  a5xx_flush (struct msm_gpu*,struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  a5xx_preempt_trigger (struct msm_gpu*) ; 
 int /*<<< orphan*/  a5xx_submit_in_rb (struct msm_gpu*,struct msm_gem_submit*,struct msm_file_private*) ; 
 int /*<<< orphan*/  fence ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbmemptr (struct msm_ringbuffer*,int /*<<< orphan*/ ) ; 
 struct a5xx_gpu* to_a5xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a5xx_submit(struct msm_gpu *gpu, struct msm_gem_submit *submit,
	struct msm_file_private *ctx)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	struct msm_drm_private *priv = gpu->dev->dev_private;
	struct msm_ringbuffer *ring = submit->ring;
	unsigned int i, ibs = 0;

	if (IS_ENABLED(CONFIG_DRM_MSM_GPU_SUDO) && submit->in_rb) {
		priv->lastctx = NULL;
		a5xx_submit_in_rb(gpu, submit, ctx);
		return;
	}

	OUT_PKT7(ring, CP_PREEMPT_ENABLE_GLOBAL, 1);
	OUT_RING(ring, 0x02);

	/* Turn off protected mode to write to special registers */
	OUT_PKT7(ring, CP_SET_PROTECTED_MODE, 1);
	OUT_RING(ring, 0);

	/* Set the save preemption record for the ring/command */
	OUT_PKT4(ring, REG_A5XX_CP_CONTEXT_SWITCH_SAVE_ADDR_LO, 2);
	OUT_RING(ring, lower_32_bits(a5xx_gpu->preempt_iova[submit->ring->id]));
	OUT_RING(ring, upper_32_bits(a5xx_gpu->preempt_iova[submit->ring->id]));

	/* Turn back on protected mode */
	OUT_PKT7(ring, CP_SET_PROTECTED_MODE, 1);
	OUT_RING(ring, 1);

	/* Enable local preemption for finegrain preemption */
	OUT_PKT7(ring, CP_PREEMPT_ENABLE_GLOBAL, 1);
	OUT_RING(ring, 0x02);

	/* Allow CP_CONTEXT_SWITCH_YIELD packets in the IB2 */
	OUT_PKT7(ring, CP_YIELD_ENABLE, 1);
	OUT_RING(ring, 0x02);

	/* Submit the commands */
	for (i = 0; i < submit->nr_cmds; i++) {
		switch (submit->cmd[i].type) {
		case MSM_SUBMIT_CMD_IB_TARGET_BUF:
			break;
		case MSM_SUBMIT_CMD_CTX_RESTORE_BUF:
			if (priv->lastctx == ctx)
				break;
			/* fall-thru */
		case MSM_SUBMIT_CMD_BUF:
			OUT_PKT7(ring, CP_INDIRECT_BUFFER_PFE, 3);
			OUT_RING(ring, lower_32_bits(submit->cmd[i].iova));
			OUT_RING(ring, upper_32_bits(submit->cmd[i].iova));
			OUT_RING(ring, submit->cmd[i].size);
			ibs++;
			break;
		}
	}

	/*
	 * Write the render mode to NULL (0) to indicate to the CP that the IBs
	 * are done rendering - otherwise a lucky preemption would start
	 * replaying from the last checkpoint
	 */
	OUT_PKT7(ring, CP_SET_RENDER_MODE, 5);
	OUT_RING(ring, 0);
	OUT_RING(ring, 0);
	OUT_RING(ring, 0);
	OUT_RING(ring, 0);
	OUT_RING(ring, 0);

	/* Turn off IB level preemptions */
	OUT_PKT7(ring, CP_YIELD_ENABLE, 1);
	OUT_RING(ring, 0x01);

	/* Write the fence to the scratch register */
	OUT_PKT4(ring, REG_A5XX_CP_SCRATCH_REG(2), 1);
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

	/* Yield the floor on command completion */
	OUT_PKT7(ring, CP_CONTEXT_SWITCH_YIELD, 4);
	/*
	 * If dword[2:1] are non zero, they specify an address for the CP to
	 * write the value of dword[3] to on preemption complete. Write 0 to
	 * skip the write
	 */
	OUT_RING(ring, 0x00);
	OUT_RING(ring, 0x00);
	/* Data value - not used if the address above is 0 */
	OUT_RING(ring, 0x01);
	/* Set bit 0 to trigger an interrupt on preempt complete */
	OUT_RING(ring, 0x01);

	a5xx_flush(gpu, ring);

	/* Check to see if we need to start preemption */
	a5xx_preempt_trigger(gpu);
}