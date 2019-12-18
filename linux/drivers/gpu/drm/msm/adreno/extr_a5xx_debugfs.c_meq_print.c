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
struct msm_gpu {int dummy; } ;
struct drm_printer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_A5XX_CP_MEQ_DBG_ADDR ; 
 int /*<<< orphan*/  REG_A5XX_CP_MEQ_DBG_DATA ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,...) ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meq_print(struct msm_gpu *gpu, struct drm_printer *p)
{
	int i;

	drm_printf(p, "MEQ state:\n");
	gpu_write(gpu, REG_A5XX_CP_MEQ_DBG_ADDR, 0);

	for (i = 0; i < 64; i++) {
		drm_printf(p, "  %02x: %08x\n", i,
			gpu_read(gpu, REG_A5XX_CP_MEQ_DBG_DATA));
	}

	return 0;
}