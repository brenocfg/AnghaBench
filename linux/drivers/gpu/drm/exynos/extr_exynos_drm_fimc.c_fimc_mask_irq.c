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
struct fimc_context {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  EXYNOS_CIGCTRL ; 
 int EXYNOS_CIGCTRL_IRQ_ENABLE ; 
 int EXYNOS_CIGCTRL_IRQ_LEVEL ; 
 int EXYNOS_CIGCTRL_IRQ_OVFEN ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_mask_irq(struct fimc_context *ctx, bool enable)
{
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "enable[%d]\n", enable);

	cfg = fimc_read(ctx, EXYNOS_CIGCTRL);
	if (enable) {
		cfg &= ~EXYNOS_CIGCTRL_IRQ_OVFEN;
		cfg |= EXYNOS_CIGCTRL_IRQ_ENABLE | EXYNOS_CIGCTRL_IRQ_LEVEL;
	} else
		cfg &= ~EXYNOS_CIGCTRL_IRQ_ENABLE;
	fimc_write(ctx, cfg, EXYNOS_CIGCTRL);
}