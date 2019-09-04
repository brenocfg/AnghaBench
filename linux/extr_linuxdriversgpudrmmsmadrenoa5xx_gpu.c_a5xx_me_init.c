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
struct msm_ringbuffer {int dummy; } ;
struct msm_gpu {TYPE_1__* funcs; struct msm_ringbuffer** rb; } ;
struct adreno_gpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush ) (struct msm_gpu*,struct msm_ringbuffer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ME_INIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUT_PKT7 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (struct msm_ringbuffer*,int) ; 
 scalar_t__ a5xx_idle (struct msm_gpu*,struct msm_ringbuffer*) ; 
 scalar_t__ adreno_is_a530 (struct adreno_gpu*) ; 
 int /*<<< orphan*/  stub1 (struct msm_gpu*,struct msm_ringbuffer*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static int a5xx_me_init(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct msm_ringbuffer *ring = gpu->rb[0];

	OUT_PKT7(ring, CP_ME_INIT, 8);

	OUT_RING(ring, 0x0000002F);

	/* Enable multiple hardware contexts */
	OUT_RING(ring, 0x00000003);

	/* Enable error detection */
	OUT_RING(ring, 0x20000000);

	/* Don't enable header dump */
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	/* Specify workarounds for various microcode issues */
	if (adreno_is_a530(adreno_gpu)) {
		/* Workaround for token end syncs
		 * Force a WFI after every direct-render 3D mode draw and every
		 * 2D mode 3 draw
		 */
		OUT_RING(ring, 0x0000000B);
	} else {
		/* No workarounds enabled */
		OUT_RING(ring, 0x00000000);
	}

	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	gpu->funcs->flush(gpu, ring);
	return a5xx_idle(gpu, ring) ? 0 : -EINVAL;
}