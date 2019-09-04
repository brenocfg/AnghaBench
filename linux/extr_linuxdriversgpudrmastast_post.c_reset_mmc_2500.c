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
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void reset_mmc_2500(struct ast_private *ast)
{
	ast_moutdwm(ast, 0x1E78505C, 0x00000004);
	ast_moutdwm(ast, 0x1E785044, 0x00000001);
	ast_moutdwm(ast, 0x1E785048, 0x00004755);
	ast_moutdwm(ast, 0x1E78504C, 0x00000013);
	mdelay(100);
	ast_moutdwm(ast, 0x1E785054, 0x00000077);
	ast_moutdwm(ast, 0x1E6E0000, 0xFC600309);
}