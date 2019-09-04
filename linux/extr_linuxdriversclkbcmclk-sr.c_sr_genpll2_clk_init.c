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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_pll_clk_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr_genpll2 ; 
 int /*<<< orphan*/  sr_genpll2_clk ; 

__attribute__((used)) static int sr_genpll2_clk_init(struct platform_device *pdev)
{
	iproc_pll_clk_setup(pdev->dev.of_node,
			    &sr_genpll2, NULL, 0, sr_genpll2_clk,
			    ARRAY_SIZE(sr_genpll2_clk));
	return 0;
}