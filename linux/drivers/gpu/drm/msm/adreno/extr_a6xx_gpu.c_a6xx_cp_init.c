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
struct msm_ringbuffer {int dummy; } ;
struct msm_gpu {struct msm_ringbuffer** rb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ME_INIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUT_PKT7 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (struct msm_ringbuffer*,int) ; 
 int /*<<< orphan*/  a6xx_flush (struct msm_gpu*,struct msm_ringbuffer*) ; 
 scalar_t__ a6xx_idle (struct msm_gpu*,struct msm_ringbuffer*) ; 

__attribute__((used)) static int a6xx_cp_init(struct msm_gpu *gpu)
{
	struct msm_ringbuffer *ring = gpu->rb[0];

	OUT_PKT7(ring, CP_ME_INIT, 8);

	OUT_RING(ring, 0x0000002f);

	/* Enable multiple hardware contexts */
	OUT_RING(ring, 0x00000003);

	/* Enable error detection */
	OUT_RING(ring, 0x20000000);

	/* Don't enable header dump */
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	/* No workarounds enabled */
	OUT_RING(ring, 0x00000000);

	/* Pad rest of the cmds with 0's */
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	a6xx_flush(gpu, ring);
	return a6xx_idle(gpu, ring) ? 0 : -EINVAL;
}