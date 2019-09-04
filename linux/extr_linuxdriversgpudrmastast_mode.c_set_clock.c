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
typedef  int u8 ;
struct ast_private {int dummy; } ;
struct ast_i2c_chan {TYPE_1__* dev; } ;
struct TYPE_2__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int ast_get_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ast_set_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void set_clock(void *i2c_priv, int clock)
{
	struct ast_i2c_chan *i2c = i2c_priv;
	struct ast_private *ast = i2c->dev->dev_private;
	int i;
	u8 ujcrb7, jtemp;

	for (i = 0; i < 0x10000; i++) {
		ujcrb7 = ((clock & 0x01) ? 0 : 1);
		ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0xf4, ujcrb7);
		jtemp = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x01);
		if (ujcrb7 == jtemp)
			break;
	}
}