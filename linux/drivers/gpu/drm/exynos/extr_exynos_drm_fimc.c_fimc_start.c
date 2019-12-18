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
struct fimc_context {int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS_CIGCTRL ; 
 int /*<<< orphan*/  EXYNOS_CIGCTRL_IRQ_END_DISABLE ; 
 int /*<<< orphan*/  EXYNOS_CIIMGCPT ; 
 int EXYNOS_CIIMGCPT_IMGCPTEN ; 
 int EXYNOS_CIIMGCPT_IMGCPTEN_SC ; 
 int /*<<< orphan*/  EXYNOS_CIOCTRL ; 
 int /*<<< orphan*/  EXYNOS_CIOCTRL_WEAVE_MASK ; 
 int /*<<< orphan*/  EXYNOS_CISCCTRL ; 
 int EXYNOS_CISCCTRL_PROGRESSIVE ; 
 int EXYNOS_CISCCTRL_SCALERSTART ; 
 int EXYNOS_CISCCTRL_SCAN_MASK ; 
 int /*<<< orphan*/  EXYNOS_CISTATUS ; 
 int /*<<< orphan*/  EXYNOS_MSCTRL ; 
 int /*<<< orphan*/  EXYNOS_MSCTRL_ENVID ; 
 int EXYNOS_MSCTRL_INPUT_MASK ; 
 int EXYNOS_MSCTRL_INPUT_MEMORY ; 
 int /*<<< orphan*/  fimc_clear_bits (struct fimc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_handle_jpeg (struct fimc_context*,int) ; 
 int /*<<< orphan*/  fimc_handle_lastend (struct fimc_context*,int) ; 
 int /*<<< orphan*/  fimc_mask_irq (struct fimc_context*,int) ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_set_bits (struct fimc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_set_scaler (struct fimc_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fimc_set_type_ctrl (struct fimc_context*) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_start(struct fimc_context *ctx)
{
	u32 cfg0, cfg1;

	fimc_mask_irq(ctx, true);

	/* If set true, we can save jpeg about screen */
	fimc_handle_jpeg(ctx, false);
	fimc_set_scaler(ctx, &ctx->sc);

	fimc_set_type_ctrl(ctx);
	fimc_handle_lastend(ctx, false);

	/* setup dma */
	cfg0 = fimc_read(ctx, EXYNOS_MSCTRL);
	cfg0 &= ~EXYNOS_MSCTRL_INPUT_MASK;
	cfg0 |= EXYNOS_MSCTRL_INPUT_MEMORY;
	fimc_write(ctx, cfg0, EXYNOS_MSCTRL);

	/* Reset status */
	fimc_write(ctx, 0x0, EXYNOS_CISTATUS);

	cfg0 = fimc_read(ctx, EXYNOS_CIIMGCPT);
	cfg0 &= ~EXYNOS_CIIMGCPT_IMGCPTEN_SC;
	cfg0 |= EXYNOS_CIIMGCPT_IMGCPTEN_SC;

	/* Scaler */
	cfg1 = fimc_read(ctx, EXYNOS_CISCCTRL);
	cfg1 &= ~EXYNOS_CISCCTRL_SCAN_MASK;
	cfg1 |= (EXYNOS_CISCCTRL_PROGRESSIVE |
		EXYNOS_CISCCTRL_SCALERSTART);

	fimc_write(ctx, cfg1, EXYNOS_CISCCTRL);

	/* Enable image capture*/
	cfg0 |= EXYNOS_CIIMGCPT_IMGCPTEN;
	fimc_write(ctx, cfg0, EXYNOS_CIIMGCPT);

	/* Disable frame end irq */
	fimc_clear_bits(ctx, EXYNOS_CIGCTRL, EXYNOS_CIGCTRL_IRQ_END_DISABLE);

	fimc_clear_bits(ctx, EXYNOS_CIOCTRL, EXYNOS_CIOCTRL_WEAVE_MASK);

	fimc_set_bits(ctx, EXYNOS_MSCTRL, EXYNOS_MSCTRL_ENVID);
}