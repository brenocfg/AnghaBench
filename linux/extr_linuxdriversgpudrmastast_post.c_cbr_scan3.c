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
 size_t CBR_PATNUM ; 
 int /*<<< orphan*/  ast_moutdwm (struct ast_private*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cbr_test3 (struct ast_private*) ; 
 int /*<<< orphan*/ * pattern ; 

__attribute__((used)) static bool cbr_scan3(struct ast_private *ast)
{
	u32 patcnt, loop;

	for (patcnt = 0; patcnt < CBR_PATNUM; patcnt++) {
		ast_moutdwm(ast, 0x1e6e007c, pattern[patcnt]);
		for (loop = 0; loop < 2; loop++) {
			if (cbr_test3(ast))
				break;
		}
		if (loop == 2)
			return false;
	}
	return true;
}