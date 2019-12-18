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
 int /*<<< orphan*/  CP_SET_PROTECTED_MODE ; 
 int /*<<< orphan*/  OUT_PKT3 (struct msm_ringbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (struct msm_ringbuffer*,int) ; 
 int REG_A2XX_PA_SC_LINE_CNTL ; 
 int REG_A2XX_PA_SC_WINDOW_OFFSET ; 
 int REG_A2XX_PA_SU_POINT_SIZE ; 
 int REG_A2XX_PA_SU_POLY_OFFSET_FRONT_SCALE ; 
 int REG_A2XX_RB_DEPTHCONTROL ; 
 int REG_A2XX_RB_SURFACE_INFO ; 
 int REG_A2XX_SQ_PROGRAM_CNTL ; 
 int REG_A2XX_VGT_MAX_VTX_INDX ; 
 int a2xx_idle (struct msm_gpu*) ; 
 int /*<<< orphan*/  stub1 (struct msm_gpu*,struct msm_ringbuffer*) ; 

__attribute__((used)) static bool a2xx_me_init(struct msm_gpu *gpu)
{
	struct msm_ringbuffer *ring = gpu->rb[0];

	OUT_PKT3(ring, CP_ME_INIT, 18);

	/* All fields present (bits 9:0) */
	OUT_RING(ring, 0x000003ff);
	/* Disable/Enable Real-Time Stream processing (present but ignored) */
	OUT_RING(ring, 0x00000000);
	/* Enable (2D <-> 3D) implicit synchronization (present but ignored) */
	OUT_RING(ring, 0x00000000);

	OUT_RING(ring, REG_A2XX_RB_SURFACE_INFO - 0x2000);
	OUT_RING(ring, REG_A2XX_PA_SC_WINDOW_OFFSET - 0x2000);
	OUT_RING(ring, REG_A2XX_VGT_MAX_VTX_INDX - 0x2000);
	OUT_RING(ring, REG_A2XX_SQ_PROGRAM_CNTL - 0x2000);
	OUT_RING(ring, REG_A2XX_RB_DEPTHCONTROL - 0x2000);
	OUT_RING(ring, REG_A2XX_PA_SU_POINT_SIZE - 0x2000);
	OUT_RING(ring, REG_A2XX_PA_SC_LINE_CNTL - 0x2000);
	OUT_RING(ring, REG_A2XX_PA_SU_POLY_OFFSET_FRONT_SCALE - 0x2000);

	/* Vertex and Pixel Shader Start Addresses in instructions
	 * (3 DWORDS per instruction) */
	OUT_RING(ring, 0x80000180);
	/* Maximum Contexts */
	OUT_RING(ring, 0x00000001);
	/* Write Confirm Interval and The CP will wait the
	 * wait_interval * 16 clocks between polling  */
	OUT_RING(ring, 0x00000000);
	/* NQ and External Memory Swap */
	OUT_RING(ring, 0x00000000);
	/* protected mode error checking (0x1f2 is REG_AXXX_CP_INT_CNTL) */
	OUT_RING(ring, 0x200001f2);
	/* Disable header dumping and Header dump address */
	OUT_RING(ring, 0x00000000);
	/* Header dump size */
	OUT_RING(ring, 0x00000000);

	/* enable protected mode */
	OUT_PKT3(ring, CP_SET_PROTECTED_MODE, 1);
	OUT_RING(ring, 1);

	gpu->funcs->flush(gpu, ring);
	return a2xx_idle(gpu);
}