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
struct msm_gem_submit {unsigned int seqno; unsigned int nr_cmds; TYPE_2__* cmd; struct msm_ringbuffer* ring; } ;
struct msm_file_private {int dummy; } ;
struct msm_drm_private {struct msm_file_private* lastctx; } ;
struct adreno_gpu {int dummy; } ;
struct a6xx_gpu {int /*<<< orphan*/  gmu; } ;
struct TYPE_4__ {int type; int size; int /*<<< orphan*/  iova; } ;
struct TYPE_3__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int CACHE_FLUSH_TS ; 
 int /*<<< orphan*/  CP_EVENT_WRITE ; 
 int /*<<< orphan*/  CP_INDIRECT_BUFFER_PFE ; 
 unsigned int MSM_GPU_SUBMIT_STATS_COUNT ; 
#define  MSM_SUBMIT_CMD_BUF 130 
#define  MSM_SUBMIT_CMD_CTX_RESTORE_BUF 129 
#define  MSM_SUBMIT_CMD_IB_TARGET_BUF 128 
 int /*<<< orphan*/  OUT_PKT4 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_PKT7 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (struct msm_ringbuffer*,int) ; 
 int PC_CCU_INVALIDATE_COLOR ; 
 int PC_CCU_INVALIDATE_DEPTH ; 
 int /*<<< orphan*/  REG_A6XX_CP_SCRATCH_REG (int) ; 
 int /*<<< orphan*/  REG_A6XX_GMU_ALWAYS_ON_COUNTER_H ; 
 scalar_t__ REG_A6XX_GMU_ALWAYS_ON_COUNTER_L ; 
 scalar_t__ REG_A6XX_RBBM_PERFCTR_CP_0_LO ; 
 int /*<<< orphan*/  a6xx_flush (struct msm_gpu*,struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  alwayson_end ; 
 int /*<<< orphan*/  alwayson_start ; 
 int /*<<< orphan*/  cpcycles_end ; 
 int /*<<< orphan*/  cpcycles_start ; 
 int /*<<< orphan*/  fence ; 
 int /*<<< orphan*/  get_stats_counter (struct msm_ringbuffer*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmu_read64 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbmemptr (struct msm_ringbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbmemptr_stats (struct msm_ringbuffer*,unsigned int,int /*<<< orphan*/ ) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 
 int /*<<< orphan*/  trace_msm_gpu_submit_flush (struct msm_gem_submit*,int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a6xx_submit(struct msm_gpu *gpu, struct msm_gem_submit *submit,
	struct msm_file_private *ctx)
{
	unsigned int index = submit->seqno % MSM_GPU_SUBMIT_STATS_COUNT;
	struct msm_drm_private *priv = gpu->dev->dev_private;
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	struct msm_ringbuffer *ring = submit->ring;
	unsigned int i;

	get_stats_counter(ring, REG_A6XX_RBBM_PERFCTR_CP_0_LO,
		rbmemptr_stats(ring, index, cpcycles_start));

	/*
	 * For PM4 the GMU register offsets are calculated from the base of the
	 * GPU registers so we need to add 0x1a800 to the register value on A630
	 * to get the right value from PM4.
	 */
	get_stats_counter(ring, REG_A6XX_GMU_ALWAYS_ON_COUNTER_L + 0x1a800,
		rbmemptr_stats(ring, index, alwayson_start));

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
			/* fall-thru */
		case MSM_SUBMIT_CMD_BUF:
			OUT_PKT7(ring, CP_INDIRECT_BUFFER_PFE, 3);
			OUT_RING(ring, lower_32_bits(submit->cmd[i].iova));
			OUT_RING(ring, upper_32_bits(submit->cmd[i].iova));
			OUT_RING(ring, submit->cmd[i].size);
			break;
		}
	}

	get_stats_counter(ring, REG_A6XX_RBBM_PERFCTR_CP_0_LO,
		rbmemptr_stats(ring, index, cpcycles_end));
	get_stats_counter(ring, REG_A6XX_GMU_ALWAYS_ON_COUNTER_L + 0x1a800,
		rbmemptr_stats(ring, index, alwayson_end));

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

	trace_msm_gpu_submit_flush(submit,
		gmu_read64(&a6xx_gpu->gmu, REG_A6XX_GMU_ALWAYS_ON_COUNTER_L,
			REG_A6XX_GMU_ALWAYS_ON_COUNTER_H));

	a6xx_flush(gpu, ring);
}