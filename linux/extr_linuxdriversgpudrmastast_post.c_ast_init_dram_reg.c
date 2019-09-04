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
struct drm_device {struct ast_private* dev_private; } ;
struct ast_private {int chip; scalar_t__ dram_type; } ;
struct ast_dramstruct {int index; int data; } ;

/* Variables and functions */
#define  AST1100 132 
#define  AST2000 131 
#define  AST2100 130 
#define  AST2150 129 
#define  AST2200 128 
 scalar_t__ AST_DRAM_1Gx16 ; 
 scalar_t__ AST_DRAM_1Gx32 ; 
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 struct ast_dramstruct* ast1100_dram_table_data ; 
 struct ast_dramstruct* ast2000_dram_table_data ; 
 struct ast_dramstruct* ast2100_dram_table_data ; 
 int ast_get_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 
 int ast_read32 (struct ast_private*,int) ; 
 int /*<<< orphan*/  ast_write32 (struct ast_private*,int,int) ; 
 int /*<<< orphan*/  cbrdlli_ast2150 (struct ast_private*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ast_init_dram_reg(struct drm_device *dev)
{
	struct ast_private *ast = dev->dev_private;
	u8 j;
	u32 data, temp, i;
	const struct ast_dramstruct *dram_reg_info;

	j = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd0, 0xff);

	if ((j & 0x80) == 0) { /* VGA only */
		if (ast->chip == AST2000) {
			dram_reg_info = ast2000_dram_table_data;
			ast_write32(ast, 0xf004, 0x1e6e0000);
			ast_write32(ast, 0xf000, 0x1);
			ast_write32(ast, 0x10100, 0xa8);

			do {
				;
			} while (ast_read32(ast, 0x10100) != 0xa8);
		} else {/* AST2100/1100 */
			if (ast->chip == AST2100 || ast->chip == 2200)
				dram_reg_info = ast2100_dram_table_data;
			else
				dram_reg_info = ast1100_dram_table_data;

			ast_write32(ast, 0xf004, 0x1e6e0000);
			ast_write32(ast, 0xf000, 0x1);
			ast_write32(ast, 0x12000, 0x1688A8A8);
			do {
				;
			} while (ast_read32(ast, 0x12000) != 0x01);

			ast_write32(ast, 0x10000, 0xfc600309);
			do {
				;
			} while (ast_read32(ast, 0x10000) != 0x01);
		}

		while (dram_reg_info->index != 0xffff) {
			if (dram_reg_info->index == 0xff00) {/* delay fn */
				for (i = 0; i < 15; i++)
					udelay(dram_reg_info->data);
			} else if (dram_reg_info->index == 0x4 && ast->chip != AST2000) {
				data = dram_reg_info->data;
				if (ast->dram_type == AST_DRAM_1Gx16)
					data = 0x00000d89;
				else if (ast->dram_type == AST_DRAM_1Gx32)
					data = 0x00000c8d;

				temp = ast_read32(ast, 0x12070);
				temp &= 0xc;
				temp <<= 2;
				ast_write32(ast, 0x10000 + dram_reg_info->index, data | temp);
			} else
				ast_write32(ast, 0x10000 + dram_reg_info->index, dram_reg_info->data);
			dram_reg_info++;
		}

		/* AST 2100/2150 DRAM calibration */
		data = ast_read32(ast, 0x10120);
		if (data == 0x5061) { /* 266Mhz */
			data = ast_read32(ast, 0x10004);
			if (data & 0x40)
				cbrdlli_ast2150(ast, 16); /* 16 bits */
			else
				cbrdlli_ast2150(ast, 32); /* 32 bits */
		}

		switch (ast->chip) {
		case AST2000:
			temp = ast_read32(ast, 0x10140);
			ast_write32(ast, 0x10140, temp | 0x40);
			break;
		case AST1100:
		case AST2100:
		case AST2200:
		case AST2150:
			temp = ast_read32(ast, 0x1200c);
			ast_write32(ast, 0x1200c, temp & 0xfffffffd);
			temp = ast_read32(ast, 0x12040);
			ast_write32(ast, 0x12040, temp | 0x40);
			break;
		default:
			break;
		}
	}

	/* wait ready */
	do {
		j = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd0, 0xff);
	} while ((j & 0x40) == 0);
}