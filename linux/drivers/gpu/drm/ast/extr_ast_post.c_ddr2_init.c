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
struct ast2300_dram_param {int reg_MADJ; int reg_SADJ; int dram_config; int reg_AC1; int reg_AC2; int reg_DQSIC; int reg_DQIDLY; int reg_DRV; int reg_IOZ; int madj_max; int reg_MRS; int reg_EMRS; int reg_FREQ; scalar_t__ rodt; scalar_t__ wodt; } ;

/* Variables and functions */
 int ast_mindwm (struct ast_private*,int) ; 
 int /*<<< orphan*/  ast_moutdwm (struct ast_private*,int,int) ; 
 int cbr_dll2 (struct ast_private*,struct ast2300_dram_param*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ddr2_init(struct ast_private *ast, struct ast2300_dram_param *param)
{
	u32 data, data2, retry = 0;

ddr2_init_start:
	ast_moutdwm(ast, 0x1E6E0000, 0xFC600309);
	ast_moutdwm(ast, 0x1E6E0018, 0x00000100);
	ast_moutdwm(ast, 0x1E6E0024, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0064, param->reg_MADJ);
	ast_moutdwm(ast, 0x1E6E0068, param->reg_SADJ);
	udelay(10);
	ast_moutdwm(ast, 0x1E6E0064, param->reg_MADJ | 0xC0000);
	udelay(10);

	ast_moutdwm(ast, 0x1E6E0004, param->dram_config);
	ast_moutdwm(ast, 0x1E6E0008, 0x90040f);
	ast_moutdwm(ast, 0x1E6E0010, param->reg_AC1);
	ast_moutdwm(ast, 0x1E6E0014, param->reg_AC2);
	ast_moutdwm(ast, 0x1E6E0020, param->reg_DQSIC);
	ast_moutdwm(ast, 0x1E6E0080, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0084, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0088, param->reg_DQIDLY);
	ast_moutdwm(ast, 0x1E6E0018, 0x4000A130);
	ast_moutdwm(ast, 0x1E6E0018, 0x00002330);
	ast_moutdwm(ast, 0x1E6E0038, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0040, 0xFF808000);
	ast_moutdwm(ast, 0x1E6E0044, 0x88848466);
	ast_moutdwm(ast, 0x1E6E0048, 0x44440008);
	ast_moutdwm(ast, 0x1E6E004C, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0050, 0x80000000);
	ast_moutdwm(ast, 0x1E6E0050, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0054, 0);
	ast_moutdwm(ast, 0x1E6E0060, param->reg_DRV);
	ast_moutdwm(ast, 0x1E6E006C, param->reg_IOZ);
	ast_moutdwm(ast, 0x1E6E0070, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0074, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0078, 0x00000000);
	ast_moutdwm(ast, 0x1E6E007C, 0x00000000);

	/* Wait MCLK2X lock to MCLK */
	do {
		data = ast_mindwm(ast, 0x1E6E001C);
	} while (!(data & 0x08000000));
	data = ast_mindwm(ast, 0x1E6E001C);
	data = (data >> 8) & 0xff;
	while ((data & 0x08) || ((data & 0x7) < 2) || (data < 4)) {
		data2 = (ast_mindwm(ast, 0x1E6E0064) & 0xfff3ffff) + 4;
		if ((data2 & 0xff) > param->madj_max) {
			break;
		}
		ast_moutdwm(ast, 0x1E6E0064, data2);
		if (data2 & 0x00100000) {
			data2 = ((data2 & 0xff) >> 3) + 3;
		} else {
			data2 = ((data2 & 0xff) >> 2) + 5;
		}
		data = ast_mindwm(ast, 0x1E6E0068) & 0xffff00ff;
		data2 += data & 0xff;
		data = data | (data2 << 8);
		ast_moutdwm(ast, 0x1E6E0068, data);
		udelay(10);
		ast_moutdwm(ast, 0x1E6E0064, ast_mindwm(ast, 0x1E6E0064) | 0xC0000);
		udelay(10);
		data = ast_mindwm(ast, 0x1E6E0018) & 0xfffff1ff;
		ast_moutdwm(ast, 0x1E6E0018, data);
		data = data | 0x200;
		ast_moutdwm(ast, 0x1E6E0018, data);
		do {
			data = ast_mindwm(ast, 0x1E6E001C);
		} while (!(data & 0x08000000));

		data = ast_mindwm(ast, 0x1E6E001C);
		data = (data >> 8) & 0xff;
	}
	ast_moutdwm(ast, 0x1E720058, ast_mindwm(ast, 0x1E6E0008) & 0xffff);
	data = ast_mindwm(ast, 0x1E6E0018) | 0xC00;
	ast_moutdwm(ast, 0x1E6E0018, data);

	ast_moutdwm(ast, 0x1E6E0034, 0x00000001);
	ast_moutdwm(ast, 0x1E6E000C, 0x00000000);
	udelay(50);
	/* Mode Register Setting */
	ast_moutdwm(ast, 0x1E6E002C, param->reg_MRS | 0x100);
	ast_moutdwm(ast, 0x1E6E0030, param->reg_EMRS);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000005);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000007);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000003);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000001);

	ast_moutdwm(ast, 0x1E6E000C, 0x00005C08);
	ast_moutdwm(ast, 0x1E6E002C, param->reg_MRS);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000001);
	ast_moutdwm(ast, 0x1E6E0030, param->reg_EMRS | 0x380);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000003);
	ast_moutdwm(ast, 0x1E6E0030, param->reg_EMRS);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000003);

	ast_moutdwm(ast, 0x1E6E000C, 0x7FFF5C01);
	data = 0;
	if (param->wodt) {
		data = 0x500;
	}
	if (param->rodt) {
		data = data | 0x3000 | ((param->reg_AC2 & 0x60000) >> 3);
	}
	ast_moutdwm(ast, 0x1E6E0034, data | 0x3);
	ast_moutdwm(ast, 0x1E6E0120, param->reg_FREQ);

	/* Calibrate the DQSI delay */
	if ((cbr_dll2(ast, param) == false) && (retry++ < 10))
		goto ddr2_init_start;

	/* ECC Memory Initialization */
#ifdef ECC
	ast_moutdwm(ast, 0x1E6E007C, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0070, 0x221);
	do {
		data = ast_mindwm(ast, 0x1E6E0070);
	} while (!(data & 0x00001000));
	ast_moutdwm(ast, 0x1E6E0070, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0050, 0x80000000);
	ast_moutdwm(ast, 0x1E6E0050, 0x00000000);
#endif

}