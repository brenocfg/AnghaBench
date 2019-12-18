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
 int mmc_test_burst2 (struct ast_private*,int /*<<< orphan*/ ) ; 
 int mmc_test_single2 (struct ast_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 cbr_test2(struct ast_private *ast)
{
	u32 data;

	data = mmc_test_burst2(ast, 0);
	if (data == 0xffff)
		return 0;
	data |= mmc_test_single2(ast, 0);
	if (data == 0xffff)
		return 0;

	return ~data & 0xffff;
}