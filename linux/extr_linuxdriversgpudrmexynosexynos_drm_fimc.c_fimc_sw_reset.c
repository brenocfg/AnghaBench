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
typedef  int /*<<< orphan*/  u32 ;
struct fimc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS_CIFCNTSEQ ; 
 int /*<<< orphan*/  EXYNOS_CIGCTRL ; 
 int EXYNOS_CIGCTRL_SWRST ; 
 int /*<<< orphan*/  EXYNOS_CIIMGCPT ; 
 int EXYNOS_CIIMGCPT_IMGCPTEN ; 
 int EXYNOS_CIIMGCPT_IMGCPTEN_SC ; 
 int /*<<< orphan*/  EXYNOS_CISRCFMT ; 
 int EXYNOS_CISRCFMT_ITU601_8BIT ; 
 int /*<<< orphan*/  EXYNOS_CISTATUS ; 
 scalar_t__ EXYNOS_CISTATUS_GET_ENVID_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXYNOS_MSCTRL ; 
 int EXYNOS_MSCTRL_ENVID ; 
 int /*<<< orphan*/  fimc_clear_bits (struct fimc_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_set_bits (struct fimc_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_sw_reset(struct fimc_context *ctx)
{
	u32 cfg;

	/* stop dma operation */
	cfg = fimc_read(ctx, EXYNOS_CISTATUS);
	if (EXYNOS_CISTATUS_GET_ENVID_STATUS(cfg))
		fimc_clear_bits(ctx, EXYNOS_MSCTRL, EXYNOS_MSCTRL_ENVID);

	fimc_set_bits(ctx, EXYNOS_CISRCFMT, EXYNOS_CISRCFMT_ITU601_8BIT);

	/* disable image capture */
	fimc_clear_bits(ctx, EXYNOS_CIIMGCPT,
		EXYNOS_CIIMGCPT_IMGCPTEN_SC | EXYNOS_CIIMGCPT_IMGCPTEN);

	/* s/w reset */
	fimc_set_bits(ctx, EXYNOS_CIGCTRL, EXYNOS_CIGCTRL_SWRST);

	/* s/w reset complete */
	fimc_clear_bits(ctx, EXYNOS_CIGCTRL, EXYNOS_CIGCTRL_SWRST);

	/* reset sequence */
	fimc_write(ctx, 0x0, EXYNOS_CIFCNTSEQ);
}