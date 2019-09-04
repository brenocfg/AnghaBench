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
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_gpu {int dummy; } ;
struct drm_printer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_A5XX_CP_ROQ_DBG_ADDR ; 
 int /*<<< orphan*/  REG_A5XX_CP_ROQ_DBG_DATA ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,...) ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int roq_print(struct msm_gpu *gpu, struct drm_printer *p)
{
	int i;

	drm_printf(p, "ROQ state:\n");
	gpu_write(gpu, REG_A5XX_CP_ROQ_DBG_ADDR, 0);

	for (i = 0; i < 512 / 4; i++) {
		uint32_t val[4];
		int j;
		for (j = 0; j < 4; j++)
			val[j] = gpu_read(gpu, REG_A5XX_CP_ROQ_DBG_DATA);
		drm_printf(p, "  %02x: %08x %08x %08x %08x\n", i,
			val[0], val[1], val[2], val[3]);
	}

	return 0;
}