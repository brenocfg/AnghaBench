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
typedef  size_t u32 ;
struct ast_private {int dummy; } ;

/* Variables and functions */
 size_t CBR_PASSNUM_AST2150 ; 
 size_t CBR_PATNUM_AST2150 ; 
 int /*<<< orphan*/  ast_moutdwm (struct ast_private*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cbrtest_ast2150 (struct ast_private*) ; 
 int /*<<< orphan*/ * pattern_AST2150 ; 

__attribute__((used)) static int cbrscan_ast2150(struct ast_private *ast, int busw)
{
	u32 patcnt, loop;

	for (patcnt = 0; patcnt < CBR_PATNUM_AST2150; patcnt++) {
		ast_moutdwm(ast, 0x1e6e007c, pattern_AST2150[patcnt]);
		for (loop = 0; loop < CBR_PASSNUM_AST2150; loop++) {
			if (cbrtest_ast2150(ast))
				break;
		}
		if (loop == CBR_PASSNUM_AST2150)
			return 0;
	}
	return 1;
}