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

__attribute__((used)) static u32 get_fw_base(struct ast_private *ast)
{
	return ast_mindwm(ast, 0x1e6e2104) & 0x7fffffff;
}