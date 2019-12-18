#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct mvebu_pinctrl_soc_info {TYPE_1__* control_data; int /*<<< orphan*/  nmodes; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVEBU_MPPS_PER_REG ; 
 int /*<<< orphan*/ * mpp_saved_regs ; 
 struct mvebu_pinctrl_soc_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int armada_xp_pinctrl_suspend(struct platform_device *pdev,
				     pm_message_t state)
{
	struct mvebu_pinctrl_soc_info *soc =
		platform_get_drvdata(pdev);
	int i, nregs;

	nregs = DIV_ROUND_UP(soc->nmodes, MVEBU_MPPS_PER_REG);

	for (i = 0; i < nregs; i++)
		mpp_saved_regs[i] = readl(soc->control_data[0].base + i * 4);

	return 0;
}