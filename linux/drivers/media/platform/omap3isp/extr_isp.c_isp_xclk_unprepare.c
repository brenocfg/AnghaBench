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
struct isp_xclk {int /*<<< orphan*/  isp; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap3isp_put (int /*<<< orphan*/ ) ; 
 struct isp_xclk* to_isp_xclk (struct clk_hw*) ; 

__attribute__((used)) static void isp_xclk_unprepare(struct clk_hw *hw)
{
	struct isp_xclk *xclk = to_isp_xclk(hw);

	omap3isp_put(xclk->isp);
}