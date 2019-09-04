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
struct fimc_is {int /*<<< orphan*/ * clocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLK_AXI_FREQUENCY ; 
 int /*<<< orphan*/  ATCLK_MCUISP_FREQUENCY ; 
 size_t ISS_CLK_ACLK200 ; 
 size_t ISS_CLK_ACLK200_DIV ; 
 size_t ISS_CLK_ACLK400MCUISP ; 
 size_t ISS_CLK_ACLK400MCUISP_DIV ; 
 size_t ISS_CLK_ISP_DIV0 ; 
 size_t ISS_CLK_ISP_DIV1 ; 
 size_t ISS_CLK_MCUISP_DIV0 ; 
 size_t ISS_CLK_MCUISP_DIV1 ; 
 int clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_is_setup_clocks(struct fimc_is *is)
{
	int ret;

	ret = clk_set_parent(is->clocks[ISS_CLK_ACLK200],
					is->clocks[ISS_CLK_ACLK200_DIV]);
	if (ret < 0)
		return ret;

	ret = clk_set_parent(is->clocks[ISS_CLK_ACLK400MCUISP],
					is->clocks[ISS_CLK_ACLK400MCUISP_DIV]);
	if (ret < 0)
		return ret;

	ret = clk_set_rate(is->clocks[ISS_CLK_ISP_DIV0], ACLK_AXI_FREQUENCY);
	if (ret < 0)
		return ret;

	ret = clk_set_rate(is->clocks[ISS_CLK_ISP_DIV1], ACLK_AXI_FREQUENCY);
	if (ret < 0)
		return ret;

	ret = clk_set_rate(is->clocks[ISS_CLK_MCUISP_DIV0],
					ATCLK_MCUISP_FREQUENCY);
	if (ret < 0)
		return ret;

	return clk_set_rate(is->clocks[ISS_CLK_MCUISP_DIV1],
					ATCLK_MCUISP_FREQUENCY);
}