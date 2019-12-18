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
struct TYPE_2__ {int /*<<< orphan*/  (* flush ) (struct msm_gpu*,struct msm_ringbuffer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ME_INIT ; 
 int /*<<< orphan*/  OUT_PKT3 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (struct msm_ringbuffer*,int) ; 
 int a3xx_idle (struct msm_gpu*) ; 
 int /*<<< orphan*/  stub1 (struct msm_gpu*,struct msm_ringbuffer*) ; 

__attribute__((used)) static bool a3xx_me_init(struct msm_gpu *gpu)
{
	struct msm_ringbuffer *ring = gpu->rb[0];

	OUT_PKT3(ring, CP_ME_INIT, 17);
	OUT_RING(ring, 0x000003f7);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000080);
	OUT_RING(ring, 0x00000100);
	OUT_RING(ring, 0x00000180);
	OUT_RING(ring, 0x00006600);
	OUT_RING(ring, 0x00000150);
	OUT_RING(ring, 0x0000014e);
	OUT_RING(ring, 0x00000154);
	OUT_RING(ring, 0x00000001);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	gpu->funcs->flush(gpu, ring);
	return a3xx_idle(gpu);
}