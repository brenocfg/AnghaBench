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
typedef  int u8 ;
typedef  int u32 ;
struct ast_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int ast_get_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool wait_nack(struct ast_private *ast)
{
	u8 waitack;
	u32 retry = 0;
	do {
		waitack = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd2, 0xff);
		waitack &= 0x80;
		udelay(100);
	} while ((waitack) && (retry++ < 1000));

	if (retry < 1000)
		return true;
	else
		return false;
}