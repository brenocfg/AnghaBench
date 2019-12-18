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
 int /*<<< orphan*/  EXYNOS_CIGCTRL ; 
 int EXYNOS_CIGCTRL_SELCAM_FIMC_ITU ; 
 int EXYNOS_CIGCTRL_SELCAM_FIMC_MASK ; 
 int EXYNOS_CIGCTRL_SELCAM_ITU_A ; 
 int EXYNOS_CIGCTRL_SELCAM_ITU_MASK ; 
 int EXYNOS_CIGCTRL_SELCAM_MIPI_A ; 
 int EXYNOS_CIGCTRL_SELCAM_MIPI_MASK ; 
 int EXYNOS_CIGCTRL_SELWB_CAMIF_MASK ; 
 int EXYNOS_CIGCTRL_SELWRITEBACK_A ; 
 int EXYNOS_CIGCTRL_SELWRITEBACK_MASK ; 
 int EXYNOS_CIGCTRL_TESTPATTERN_MASK ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_set_type_ctrl(struct fimc_context *ctx)
{
	u32 cfg;

	cfg = fimc_read(ctx, EXYNOS_CIGCTRL);
	cfg &= ~(EXYNOS_CIGCTRL_TESTPATTERN_MASK |
		EXYNOS_CIGCTRL_SELCAM_ITU_MASK |
		EXYNOS_CIGCTRL_SELCAM_MIPI_MASK |
		EXYNOS_CIGCTRL_SELCAM_FIMC_MASK |
		EXYNOS_CIGCTRL_SELWB_CAMIF_MASK |
		EXYNOS_CIGCTRL_SELWRITEBACK_MASK);

	cfg |= (EXYNOS_CIGCTRL_SELCAM_ITU_A |
		EXYNOS_CIGCTRL_SELWRITEBACK_A |
		EXYNOS_CIGCTRL_SELCAM_MIPI_A |
		EXYNOS_CIGCTRL_SELCAM_FIMC_ITU);

	fimc_write(ctx, cfg, EXYNOS_CIGCTRL);
}