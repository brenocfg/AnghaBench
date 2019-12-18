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
struct drm_device {struct ast_private* dev_private; } ;
struct ast_private {scalar_t__ chip; int /*<<< orphan*/  tx_chip_type; } ;

/* Variables and functions */
 scalar_t__ AST2300 ; 
 scalar_t__ AST2400 ; 
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int /*<<< orphan*/  AST_TX_SIL164 ; 
 int ast_get_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ast_init_analog (struct drm_device*) ; 
 int /*<<< orphan*/  ast_init_dvo (struct drm_device*) ; 
 int /*<<< orphan*/  ast_launch_m68k (struct drm_device*) ; 

void ast_init_3rdtx(struct drm_device *dev)
{
	struct ast_private *ast = dev->dev_private;
	u8 jreg;

	if (ast->chip == AST2300 || ast->chip == AST2400) {
		jreg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd1, 0xff);
		switch (jreg & 0x0e) {
		case 0x04:
			ast_init_dvo(dev);
			break;
		case 0x08:
			ast_launch_m68k(dev);
			break;
		case 0x0c:
			ast_init_dvo(dev);
			break;
		default:
			if (ast->tx_chip_type == AST_TX_SIL164)
				ast_init_dvo(dev);
			else
				ast_init_analog(dev);
		}
	}
}