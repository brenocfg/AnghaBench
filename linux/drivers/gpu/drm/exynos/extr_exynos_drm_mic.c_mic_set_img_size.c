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
typedef  scalar_t__ u32 ;
struct videomode {int /*<<< orphan*/  vactive; int /*<<< orphan*/  hactive; } ;
struct exynos_mic {scalar_t__ reg; struct videomode vm; } ;

/* Variables and functions */
 scalar_t__ MIC_IMG_H_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MIC_IMG_SIZE ; 
 scalar_t__ MIC_IMG_V_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mic_set_img_size(struct exynos_mic *mic)
{
	struct videomode *vm = &mic->vm;
	u32 reg;

	reg = MIC_IMG_H_SIZE(vm->hactive) +
		MIC_IMG_V_SIZE(vm->vactive);

	writel(reg, mic->reg + MIC_IMG_SIZE);
}