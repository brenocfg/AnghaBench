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
typedef  int uint32_t ;
typedef  int u32 ;
struct ast_private {int dummy; } ;

/* Variables and functions */
 int ast_read32 (struct ast_private*,int) ; 
 int /*<<< orphan*/  ast_write32 (struct ast_private*,int,int) ; 

u32 ast_mindwm(struct ast_private *ast, u32 r)
{
	uint32_t data;

	ast_write32(ast, 0xf004, r & 0xffff0000);
	ast_write32(ast, 0xf000, 0x1);

	do {
		data = ast_read32(ast, 0xf004) & 0xffff0000;
	} while (data != (r & 0xffff0000));
	return ast_read32(ast, 0x10000 + (r & 0x0000ffff));
}