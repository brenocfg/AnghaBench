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
struct l2x0_regs {int /*<<< orphan*/  aux_ctrl; int /*<<< orphan*/  pwr_ctrl; int /*<<< orphan*/  prefetch_ctrl; int /*<<< orphan*/  data_latency; int /*<<< orphan*/  tag_latency; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_CMD_L2X0SETUP1 ; 
 int /*<<< orphan*/  SMC_CMD_L2X0SETUP2 ; 
 int /*<<< orphan*/  exynos_smc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_l2_configure(const struct l2x0_regs *regs)
{
	exynos_smc(SMC_CMD_L2X0SETUP1, regs->tag_latency, regs->data_latency,
		   regs->prefetch_ctrl);
	exynos_smc(SMC_CMD_L2X0SETUP2, regs->pwr_ctrl, regs->aux_ctrl, 0);
}