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
struct davinci_lpsc_clk {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPSC_STATE_ENABLE ; 
 int /*<<< orphan*/  davinci_lpsc_config (struct davinci_lpsc_clk*,int /*<<< orphan*/ ) ; 
 struct davinci_lpsc_clk* to_davinci_lpsc_clk (struct clk_hw*) ; 

__attribute__((used)) static int davinci_lpsc_clk_enable(struct clk_hw *hw)
{
	struct davinci_lpsc_clk *lpsc = to_davinci_lpsc_clk(hw);

	davinci_lpsc_config(lpsc, LPSC_STATE_ENABLE);

	return 0;
}