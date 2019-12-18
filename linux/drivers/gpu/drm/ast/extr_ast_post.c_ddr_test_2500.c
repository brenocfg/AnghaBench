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
struct ast_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ast_moutdwm (struct ast_private*,int,int) ; 
 int /*<<< orphan*/  mmc_test_burst (struct ast_private*,int) ; 
 int /*<<< orphan*/  mmc_test_single_2500 (struct ast_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ddr_test_2500(struct ast_private *ast)
{
	ast_moutdwm(ast, 0x1E6E0074, 0x0000FFFF);
	ast_moutdwm(ast, 0x1E6E007C, 0xFF00FF00);
	if (!mmc_test_burst(ast, 0))
		return false;
	if (!mmc_test_burst(ast, 1))
		return false;
	if (!mmc_test_burst(ast, 2))
		return false;
	if (!mmc_test_burst(ast, 3))
		return false;
	if (!mmc_test_single_2500(ast, 0))
		return false;
	return true;
}