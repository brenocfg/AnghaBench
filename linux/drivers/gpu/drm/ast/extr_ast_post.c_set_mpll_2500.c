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
 int ast_mindwm (struct ast_private*,int) ; 
 int /*<<< orphan*/  ast_moutdwm (struct ast_private*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void set_mpll_2500(struct ast_private *ast)
{
	u32 addr, data, param;

	/* Reset MMC */
	ast_moutdwm(ast, 0x1E6E0000, 0xFC600309);
	ast_moutdwm(ast, 0x1E6E0034, 0x00020080);
	for (addr = 0x1e6e0004; addr < 0x1e6e0090;) {
		ast_moutdwm(ast, addr, 0x0);
		addr += 4;
	}
	ast_moutdwm(ast, 0x1E6E0034, 0x00020000);

	ast_moutdwm(ast, 0x1E6E2000, 0x1688A8A8);
	data = ast_mindwm(ast, 0x1E6E2070) & 0x00800000;
	if (data) {
		/* CLKIN = 25MHz */
		param = 0x930023E0;
		ast_moutdwm(ast, 0x1E6E2160, 0x00011320);
	} else {
		/* CLKIN = 24MHz */
		param = 0x93002400;
	}
	ast_moutdwm(ast, 0x1E6E2020, param);
	udelay(100);
}