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
 int /*<<< orphan*/  mmc_test_burst (struct ast_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_test_single (struct ast_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cbr_test3(struct ast_private *ast)
{
	if (!mmc_test_burst(ast, 0))
		return false;
	if (!mmc_test_single(ast, 0))
		return false;
	return true;
}