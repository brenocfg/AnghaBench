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
 int TIMEOUT_AST2150 ; 
 int ast_mindwm (struct ast_private*,int) ; 
 int /*<<< orphan*/  ast_moutdwm (struct ast_private*,int,int) ; 

__attribute__((used)) static u32 mmctestburst2_ast2150(struct ast_private *ast, u32 datagen)
{
	u32 data, timeout;

	ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
	ast_moutdwm(ast, 0x1e6e0070, 0x00000001 | (datagen << 3));
	timeout = 0;
	do {
		data = ast_mindwm(ast, 0x1e6e0070) & 0x40;
		if (++timeout > TIMEOUT_AST2150) {
			ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
			return 0xffffffff;
		}
	} while (!data);
	ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
	ast_moutdwm(ast, 0x1e6e0070, 0x00000003 | (datagen << 3));
	timeout = 0;
	do {
		data = ast_mindwm(ast, 0x1e6e0070) & 0x40;
		if (++timeout > TIMEOUT_AST2150) {
			ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
			return 0xffffffff;
		}
	} while (!data);
	data = (ast_mindwm(ast, 0x1e6e0070) & 0x80) >> 7;
	ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
	return data;
}