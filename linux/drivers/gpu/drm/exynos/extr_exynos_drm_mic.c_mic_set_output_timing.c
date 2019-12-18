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
typedef  int u32 ;
struct videomode {int hactive; int vactive; scalar_t__ hfront_porch; scalar_t__ hback_porch; scalar_t__ hsync_len; } ;
struct exynos_mic {scalar_t__ reg; int /*<<< orphan*/  i80_mode; int /*<<< orphan*/  dev; struct videomode vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ MIC_2D_OUTPUT_TIMING_0 ; 
 scalar_t__ MIC_2D_OUTPUT_TIMING_1 ; 
 scalar_t__ MIC_2D_OUTPUT_TIMING_2 ; 
 int MIC_BS_SIZE_2D (int) ; 
 int MIC_HBP_SIZE_2D (scalar_t__) ; 
 int MIC_H_PERIOD_PIXEL_2D (scalar_t__) ; 
 int MIC_H_PULSE_WIDTH_2D (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mic_set_output_timing(struct exynos_mic *mic)
{
	struct videomode vm = mic->vm;
	u32 reg, bs_size_2d;

	DRM_DEV_DEBUG(mic->dev, "w: %u, h: %u\n", vm.hactive, vm.vactive);
	bs_size_2d = ((vm.hactive >> 2) << 1) + (vm.vactive % 4);
	reg = MIC_BS_SIZE_2D(bs_size_2d);
	writel(reg, mic->reg + MIC_2D_OUTPUT_TIMING_2);

	if (!mic->i80_mode) {
		reg = MIC_H_PULSE_WIDTH_2D(vm.hsync_len) +
			MIC_H_PERIOD_PIXEL_2D(vm.hsync_len + bs_size_2d +
					vm.hback_porch + vm.hfront_porch);
		writel(reg, mic->reg + MIC_2D_OUTPUT_TIMING_0);

		reg = MIC_HBP_SIZE_2D(vm.hback_porch) +
			MIC_H_PERIOD_PIXEL_2D(vm.hfront_porch);
		writel(reg, mic->reg + MIC_2D_OUTPUT_TIMING_1);
	}
}