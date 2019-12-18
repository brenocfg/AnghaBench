#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msm_ringbuffer {int dummy; } ;
struct msm_gpu {TYPE_3__* funcs; TYPE_1__* dev; } ;
struct msm_gem_submit {unsigned int nr_cmds; int seqno; TYPE_2__* cmd; struct msm_ringbuffer* ring; } ;
struct msm_file_private {int dummy; } ;
struct msm_drm_private {struct msm_file_private* lastctx; } ;
struct adreno_gpu {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* flush ) (struct msm_gpu*,struct msm_ringbuffer*) ;} ;
struct TYPE_5__ {int type; int size; int /*<<< orphan*/  iova; } ;
struct TYPE_4__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int BIT (int) ; 
 int CACHE_FLUSH_TS ; 
 int /*<<< orphan*/  CP_EVENT_WRITE ; 
 int /*<<< orphan*/  CP_INDIRECT_BUFFER_PFD ; 
 int /*<<< orphan*/  CP_INDIRECT_BUFFER_PFE ; 
 int /*<<< orphan*/  CP_INTERRUPT ; 
 int CP_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CP_SET_CONSTANT ; 
 int /*<<< orphan*/  CP_WAIT_FOR_IDLE ; 
 int HLSQ_FLUSH ; 
#define  MSM_SUBMIT_CMD_BUF 130 
#define  MSM_SUBMIT_CMD_CTX_RESTORE_BUF 129 
#define  MSM_SUBMIT_CMD_IB_TARGET_BUF 128 
 int /*<<< orphan*/  OUT_PKT0 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_PKT2 (struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  OUT_PKT3 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (struct msm_ringbuffer*,int) ; 
 int /*<<< orphan*/  REG_A3XX_HLSQ_CL_KERNEL_GROUP_X_REG ; 
 int /*<<< orphan*/  REG_AXXX_CP_SCRATCH_REG2 ; 
 int /*<<< orphan*/  adreno_is_a2xx (struct adreno_gpu*) ; 
 scalar_t__ adreno_is_a3xx (struct adreno_gpu*) ; 
 int /*<<< orphan*/  adreno_is_a430 (struct adreno_gpu*) ; 
 scalar_t__ adreno_is_a4xx (struct adreno_gpu*) ; 
 int /*<<< orphan*/  fence ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int rbmemptr (struct msm_ringbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct msm_gpu*,struct msm_ringbuffer*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

void adreno_submit(struct msm_gpu *gpu, struct msm_gem_submit *submit,
		struct msm_file_private *ctx)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct msm_drm_private *priv = gpu->dev->dev_private;
	struct msm_ringbuffer *ring = submit->ring;
	unsigned i;

	for (i = 0; i < submit->nr_cmds; i++) {
		switch (submit->cmd[i].type) {
		case MSM_SUBMIT_CMD_IB_TARGET_BUF:
			/* ignore IB-targets */
			break;
		case MSM_SUBMIT_CMD_CTX_RESTORE_BUF:
			/* ignore if there has not been a ctx switch: */
			if (priv->lastctx == ctx)
				break;
			/* fall-thru */
		case MSM_SUBMIT_CMD_BUF:
			OUT_PKT3(ring, adreno_is_a430(adreno_gpu) ?
				CP_INDIRECT_BUFFER_PFE : CP_INDIRECT_BUFFER_PFD, 2);
			OUT_RING(ring, lower_32_bits(submit->cmd[i].iova));
			OUT_RING(ring, submit->cmd[i].size);
			OUT_PKT2(ring);
			break;
		}
	}

	OUT_PKT0(ring, REG_AXXX_CP_SCRATCH_REG2, 1);
	OUT_RING(ring, submit->seqno);

	if (adreno_is_a3xx(adreno_gpu) || adreno_is_a4xx(adreno_gpu)) {
		/* Flush HLSQ lazy updates to make sure there is nothing
		 * pending for indirect loads after the timestamp has
		 * passed:
		 */
		OUT_PKT3(ring, CP_EVENT_WRITE, 1);
		OUT_RING(ring, HLSQ_FLUSH);
	}

	/* wait for idle before cache flush/interrupt */
	OUT_PKT3(ring, CP_WAIT_FOR_IDLE, 1);
	OUT_RING(ring, 0x00000000);

	if (!adreno_is_a2xx(adreno_gpu)) {
		/* BIT(31) of CACHE_FLUSH_TS triggers CACHE_FLUSH_TS IRQ from GPU */
		OUT_PKT3(ring, CP_EVENT_WRITE, 3);
		OUT_RING(ring, CACHE_FLUSH_TS | BIT(31));
		OUT_RING(ring, rbmemptr(ring, fence));
		OUT_RING(ring, submit->seqno);
	} else {
		/* BIT(31) means something else on a2xx */
		OUT_PKT3(ring, CP_EVENT_WRITE, 3);
		OUT_RING(ring, CACHE_FLUSH_TS);
		OUT_RING(ring, rbmemptr(ring, fence));
		OUT_RING(ring, submit->seqno);
		OUT_PKT3(ring, CP_INTERRUPT, 1);
		OUT_RING(ring, 0x80000000);
	}

#if 0
	if (adreno_is_a3xx(adreno_gpu)) {
		/* Dummy set-constant to trigger context rollover */
		OUT_PKT3(ring, CP_SET_CONSTANT, 2);
		OUT_RING(ring, CP_REG(REG_A3XX_HLSQ_CL_KERNEL_GROUP_X_REG));
		OUT_RING(ring, 0x00000000);
	}
#endif

	gpu->funcs->flush(gpu, ring);
}