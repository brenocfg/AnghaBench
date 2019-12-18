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
 int CBR_THRESHOLD_AST2150 ; 
 int /*<<< orphan*/  ast_moutdwm (struct ast_private*,int,int) ; 
 int cbrscan_ast2150 (struct ast_private*,int) ; 

__attribute__((used)) static void cbrdlli_ast2150(struct ast_private *ast, int busw)
{
	u32 dll_min[4], dll_max[4], dlli, data, passcnt;

cbr_start:
	dll_min[0] = dll_min[1] = dll_min[2] = dll_min[3] = 0xff;
	dll_max[0] = dll_max[1] = dll_max[2] = dll_max[3] = 0x0;
	passcnt = 0;

	for (dlli = 0; dlli < 100; dlli++) {
		ast_moutdwm(ast, 0x1e6e0068, dlli | (dlli << 8) | (dlli << 16) | (dlli << 24));
		data = cbrscan_ast2150(ast, busw);
		if (data != 0) {
			if (data & 0x1) {
				if (dll_min[0] > dlli)
					dll_min[0] = dlli;
				if (dll_max[0] < dlli)
					dll_max[0] = dlli;
			}
			passcnt++;
		} else if (passcnt >= CBR_THRESHOLD_AST2150)
			goto cbr_start;
	}
	if (dll_max[0] == 0 || (dll_max[0]-dll_min[0]) < CBR_THRESHOLD_AST2150)
		goto cbr_start;

	dlli = dll_min[0] + (((dll_max[0] - dll_min[0]) * 7) >> 4);
	ast_moutdwm(ast, 0x1e6e0068, dlli | (dlli << 8) | (dlli << 16) | (dlli << 24));
}