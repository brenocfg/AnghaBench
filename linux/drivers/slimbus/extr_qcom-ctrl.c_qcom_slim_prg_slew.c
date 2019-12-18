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
struct resource {int /*<<< orphan*/  start; } ;
struct qcom_slim_ctrl {int /*<<< orphan*/  slew_reg; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_slim_prg_slew(struct platform_device *pdev,
				struct qcom_slim_ctrl *ctrl)
{
	struct resource	*slew_mem;

	if (!ctrl->slew_reg) {
		/* SLEW RATE register for this SLIMbus */
		slew_mem = platform_get_resource_byname(pdev, IORESOURCE_MEM,
				"slew");
		ctrl->slew_reg = devm_ioremap(&pdev->dev, slew_mem->start,
				resource_size(slew_mem));
		if (!ctrl->slew_reg)
			return;
	}

	writel_relaxed(1, ctrl->slew_reg);
	/* Make sure SLIMbus-slew rate enabling goes through */
	wmb();
}