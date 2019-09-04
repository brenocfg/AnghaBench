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
struct fimc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS_CIFCNTSEQ ; 
 int /*<<< orphan*/  EXYNOS_CIGCTRL ; 
 int /*<<< orphan*/  EXYNOS_CIGCTRL_IRQ_END_DISABLE ; 
 int /*<<< orphan*/  EXYNOS_CIIMGCPT ; 
 int EXYNOS_CIIMGCPT_IMGCPTEN ; 
 int EXYNOS_CIIMGCPT_IMGCPTEN_SC ; 
 int /*<<< orphan*/  EXYNOS_CISCCTRL ; 
 int EXYNOS_CISCCTRL_SCALERSTART ; 
 int /*<<< orphan*/  EXYNOS_MSCTRL ; 
 int EXYNOS_MSCTRL_ENVID ; 
 int EXYNOS_MSCTRL_INPUT_MASK ; 
 int /*<<< orphan*/  fimc_clear_bits (struct fimc_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fimc_mask_irq (struct fimc_context*,int) ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_set_bits (struct fimc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_stop(struct fimc_context *ctx)
{
	u32 cfg;

	/* Source clear */
	cfg = fimc_read(ctx, EXYNOS_MSCTRL);
	cfg &= ~EXYNOS_MSCTRL_INPUT_MASK;
	cfg &= ~EXYNOS_MSCTRL_ENVID;
	fimc_write(ctx, cfg, EXYNOS_MSCTRL);

	fimc_mask_irq(ctx, false);

	/* reset sequence */
	fimc_write(ctx, 0x0, EXYNOS_CIFCNTSEQ);

	/* Scaler disable */
	fimc_clear_bits(ctx, EXYNOS_CISCCTRL, EXYNOS_CISCCTRL_SCALERSTART);

	/* Disable image capture */
	fimc_clear_bits(ctx, EXYNOS_CIIMGCPT,
		EXYNOS_CIIMGCPT_IMGCPTEN_SC | EXYNOS_CIIMGCPT_IMGCPTEN);

	/* Enable frame end irq */
	fimc_set_bits(ctx, EXYNOS_CIGCTRL, EXYNOS_CIGCTRL_IRQ_END_DISABLE);
}