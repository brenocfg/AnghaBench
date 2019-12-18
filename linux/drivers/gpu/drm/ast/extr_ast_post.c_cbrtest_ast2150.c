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
 scalar_t__ mmctestburst2_ast2150 (struct ast_private*,int) ; 

__attribute__((used)) static int cbrtest_ast2150(struct ast_private *ast)
{
	int i;

	for (i = 0; i < 8; i++)
		if (mmctestburst2_ast2150(ast, i))
			return 0;
	return 1;
}