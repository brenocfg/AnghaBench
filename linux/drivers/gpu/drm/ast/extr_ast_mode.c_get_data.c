#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ast_private {int dummy; } ;
struct ast_i2c_chan {TYPE_1__* dev; } ;
struct TYPE_2__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int ast_get_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int get_data(void *i2c_priv)
{
	struct ast_i2c_chan *i2c = i2c_priv;
	struct ast_private *ast = i2c->dev->dev_private;
	uint32_t val, val2, count, pass;

	count = 0;
	pass = 0;
	val = (ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x20) >> 5) & 0x01;
	do {
		val2 = (ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x20) >> 5) & 0x01;
		if (val == val2) {
			pass++;
		} else {
			pass = 0;
			val = (ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x20) >> 5) & 0x01;
		}
	} while ((pass < 5) && (count++ < 0x10000));

	return val & 1 ? 1 : 0;
}