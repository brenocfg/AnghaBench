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
struct tegra_clk_pll_params {int dummy; } ;

/* Variables and functions */
 int PLLCX_MISC0_DEFAULT_VALUE ; 
 int PLLCX_MISC0_RESET ; 
 int /*<<< orphan*/  PLLCX_MISC0_WRITE_MASK ; 
 int PLLCX_MISC1_DEFAULT_VALUE ; 
 int PLLCX_MISC1_IDDQ ; 
 int /*<<< orphan*/  PLLCX_MISC1_WRITE_MASK ; 
 int PLLCX_MISC2_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PLLCX_MISC2_WRITE_MASK ; 
 int PLLCX_MISC3_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PLLCX_MISC3_WRITE_MASK ; 
 int /*<<< orphan*/  _pll_misc_chk_default (int /*<<< orphan*/ ,struct tegra_clk_pll_params*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_base ; 

__attribute__((used)) static void pllcx_check_defaults(struct tegra_clk_pll_params *params)
{
	u32 default_val;

	default_val = PLLCX_MISC0_DEFAULT_VALUE & (~PLLCX_MISC0_RESET);
	_pll_misc_chk_default(clk_base, params, 0, default_val,
			PLLCX_MISC0_WRITE_MASK);

	default_val = PLLCX_MISC1_DEFAULT_VALUE & (~PLLCX_MISC1_IDDQ);
	_pll_misc_chk_default(clk_base, params, 1, default_val,
			PLLCX_MISC1_WRITE_MASK);

	default_val = PLLCX_MISC2_DEFAULT_VALUE;
	_pll_misc_chk_default(clk_base, params, 2, default_val,
			PLLCX_MISC2_WRITE_MASK);

	default_val = PLLCX_MISC3_DEFAULT_VALUE;
	_pll_misc_chk_default(clk_base, params, 3, default_val,
			PLLCX_MISC3_WRITE_MASK);
}