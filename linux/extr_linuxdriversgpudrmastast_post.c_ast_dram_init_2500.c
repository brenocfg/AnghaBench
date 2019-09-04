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
struct ast_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ast2500_ddr3_1600_timing_table ; 
 int /*<<< orphan*/  ast2500_ddr4_1600_timing_table ; 
 int ast_mindwm (struct ast_private*,int) ; 
 int /*<<< orphan*/  ast_moutdwm (struct ast_private*,int,int) ; 
 int /*<<< orphan*/  ddr3_init_2500 (struct ast_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddr4_init_2500 (struct ast_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddr_init_common_2500 (struct ast_private*) ; 
 int /*<<< orphan*/  ddr_test_2500 (struct ast_private*) ; 
 int /*<<< orphan*/  reset_mmc_2500 (struct ast_private*) ; 
 int /*<<< orphan*/  set_mpll_2500 (struct ast_private*) ; 

__attribute__((used)) static bool ast_dram_init_2500(struct ast_private *ast)
{
	u32 data;
	u32 max_tries = 5;

	do {
		if (max_tries-- == 0)
			return false;
		set_mpll_2500(ast);
		reset_mmc_2500(ast);
		ddr_init_common_2500(ast);

		data = ast_mindwm(ast, 0x1E6E2070);
		if (data & 0x01000000)
			ddr4_init_2500(ast, ast2500_ddr4_1600_timing_table);
		else
			ddr3_init_2500(ast, ast2500_ddr3_1600_timing_table);
	} while (!ddr_test_2500(ast));

	ast_moutdwm(ast, 0x1E6E2040, ast_mindwm(ast, 0x1E6E2040) | 0x41);

	/* Patch code */
	data = ast_mindwm(ast, 0x1E6E200C) & 0xF9FFFFFF;
	ast_moutdwm(ast, 0x1E6E200C, data | 0x10000000);

	return true;
}