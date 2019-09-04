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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u16 ;
struct ast_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ast_io_write16 (struct ast_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ast_set_index_reg(struct ast_private *ast,
				     uint32_t base, uint8_t index,
				     uint8_t val)
{
	ast_io_write16(ast, base, ((u16)val << 8) | index);
}