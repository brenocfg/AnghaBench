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
typedef  int /*<<< orphan*/  u8 ;
struct ast_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IO_DAC_DATA ; 
 int /*<<< orphan*/  AST_IO_DAC_INDEX_WRITE ; 
 int /*<<< orphan*/  AST_IO_SEQ_PORT ; 
 int /*<<< orphan*/  ast_io_read8 (struct ast_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ast_io_write8 (struct ast_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ast_load_palette_index(struct ast_private *ast,
				     u8 index, u8 red, u8 green,
				     u8 blue)
{
	ast_io_write8(ast, AST_IO_DAC_INDEX_WRITE, index);
	ast_io_read8(ast, AST_IO_SEQ_PORT);
	ast_io_write8(ast, AST_IO_DAC_DATA, red);
	ast_io_read8(ast, AST_IO_SEQ_PORT);
	ast_io_write8(ast, AST_IO_DAC_DATA, green);
	ast_io_read8(ast, AST_IO_SEQ_PORT);
	ast_io_write8(ast, AST_IO_DAC_DATA, blue);
	ast_io_read8(ast, AST_IO_SEQ_PORT);
}