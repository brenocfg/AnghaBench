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
struct ast2300_dram_param {int reg_MADJ; int reg_SADJ; int reg_DRV; int reg_PERIOD; int dram_freq; int rodt; int wodt; int reg_AC1; int reg_AC2; int reg_DQSIC; int reg_MRS; int reg_EMRS; int reg_IOZ; int reg_DQIDLY; int reg_FREQ; int madj_max; int dll2_finetune_step; int dram_chipid; int dram_config; int vram_size; } ;

/* Variables and functions */
#define  AST_DRAM_1Gx16 135 
#define  AST_DRAM_2Gx16 134 
#define  AST_DRAM_4Gx16 133 
#define  AST_DRAM_512Mx16 132 
#define  AST_VIDMEM_SIZE_16M 131 
#define  AST_VIDMEM_SIZE_32M 130 
#define  AST_VIDMEM_SIZE_64M 129 
#define  AST_VIDMEM_SIZE_8M 128 
 int ast_mindwm (struct ast_private*,int) ; 
 int /*<<< orphan*/  ast_moutdwm (struct ast_private*,int,int) ; 

__attribute__((used)) static void get_ddr3_info(struct ast_private *ast, struct ast2300_dram_param *param)
{
	u32 trap, trap_AC2, trap_MRS;

	ast_moutdwm(ast, 0x1E6E2000, 0x1688A8A8);

	/* Ger trap info */
	trap = (ast_mindwm(ast, 0x1E6E2070) >> 25) & 0x3;
	trap_AC2  = 0x00020000 + (trap << 16);
	trap_AC2 |= 0x00300000 + ((trap & 0x2) << 19);
	trap_MRS  = 0x00000010 + (trap << 4);
	trap_MRS |= ((trap & 0x2) << 18);

	param->reg_MADJ       = 0x00034C4C;
	param->reg_SADJ       = 0x00001800;
	param->reg_DRV        = 0x000000F0;
	param->reg_PERIOD     = param->dram_freq;
	param->rodt           = 0;

	switch (param->dram_freq) {
	case 336:
		ast_moutdwm(ast, 0x1E6E2020, 0x0190);
		param->wodt          = 0;
		param->reg_AC1       = 0x22202725;
		param->reg_AC2       = 0xAA007613 | trap_AC2;
		param->reg_DQSIC     = 0x000000BA;
		param->reg_MRS       = 0x04001400 | trap_MRS;
		param->reg_EMRS      = 0x00000000;
		param->reg_IOZ       = 0x00000023;
		param->reg_DQIDLY    = 0x00000074;
		param->reg_FREQ      = 0x00004DC0;
		param->madj_max      = 96;
		param->dll2_finetune_step = 3;
		switch (param->dram_chipid) {
		default:
		case AST_DRAM_512Mx16:
		case AST_DRAM_1Gx16:
			param->reg_AC2   = 0xAA007613 | trap_AC2;
			break;
		case AST_DRAM_2Gx16:
			param->reg_AC2   = 0xAA00761C | trap_AC2;
			break;
		case AST_DRAM_4Gx16:
			param->reg_AC2   = 0xAA007636 | trap_AC2;
			break;
		}
		break;
	default:
	case 396:
		ast_moutdwm(ast, 0x1E6E2020, 0x03F1);
		param->wodt          = 1;
		param->reg_AC1       = 0x33302825;
		param->reg_AC2       = 0xCC009617 | trap_AC2;
		param->reg_DQSIC     = 0x000000E2;
		param->reg_MRS       = 0x04001600 | trap_MRS;
		param->reg_EMRS      = 0x00000000;
		param->reg_IOZ       = 0x00000034;
		param->reg_DRV       = 0x000000FA;
		param->reg_DQIDLY    = 0x00000089;
		param->reg_FREQ      = 0x00005040;
		param->madj_max      = 96;
		param->dll2_finetune_step = 4;

		switch (param->dram_chipid) {
		default:
		case AST_DRAM_512Mx16:
		case AST_DRAM_1Gx16:
			param->reg_AC2   = 0xCC009617 | trap_AC2;
			break;
		case AST_DRAM_2Gx16:
			param->reg_AC2   = 0xCC009622 | trap_AC2;
			break;
		case AST_DRAM_4Gx16:
			param->reg_AC2   = 0xCC00963F | trap_AC2;
			break;
		}
		break;

	case 408:
		ast_moutdwm(ast, 0x1E6E2020, 0x01F0);
		param->wodt          = 1;
		param->reg_AC1       = 0x33302825;
		param->reg_AC2       = 0xCC009617 | trap_AC2;
		param->reg_DQSIC     = 0x000000E2;
		param->reg_MRS       = 0x04001600 | trap_MRS;
		param->reg_EMRS      = 0x00000000;
		param->reg_IOZ       = 0x00000023;
		param->reg_DRV       = 0x000000FA;
		param->reg_DQIDLY    = 0x00000089;
		param->reg_FREQ      = 0x000050C0;
		param->madj_max      = 96;
		param->dll2_finetune_step = 4;

		switch (param->dram_chipid) {
		default:
		case AST_DRAM_512Mx16:
		case AST_DRAM_1Gx16:
			param->reg_AC2   = 0xCC009617 | trap_AC2;
			break;
		case AST_DRAM_2Gx16:
			param->reg_AC2   = 0xCC009622 | trap_AC2;
			break;
		case AST_DRAM_4Gx16:
			param->reg_AC2   = 0xCC00963F | trap_AC2;
			break;
		}

		break;
	case 456:
		ast_moutdwm(ast, 0x1E6E2020, 0x0230);
		param->wodt          = 0;
		param->reg_AC1       = 0x33302926;
		param->reg_AC2       = 0xCD44961A;
		param->reg_DQSIC     = 0x000000FC;
		param->reg_MRS       = 0x00081830;
		param->reg_EMRS      = 0x00000000;
		param->reg_IOZ       = 0x00000045;
		param->reg_DQIDLY    = 0x00000097;
		param->reg_FREQ      = 0x000052C0;
		param->madj_max      = 88;
		param->dll2_finetune_step = 4;
		break;
	case 504:
		ast_moutdwm(ast, 0x1E6E2020, 0x0270);
		param->wodt          = 1;
		param->reg_AC1       = 0x33302926;
		param->reg_AC2       = 0xDE44A61D;
		param->reg_DQSIC     = 0x00000117;
		param->reg_MRS       = 0x00081A30;
		param->reg_EMRS      = 0x00000000;
		param->reg_IOZ       = 0x070000BB;
		param->reg_DQIDLY    = 0x000000A0;
		param->reg_FREQ      = 0x000054C0;
		param->madj_max      = 79;
		param->dll2_finetune_step = 4;
		break;
	case 528:
		ast_moutdwm(ast, 0x1E6E2020, 0x0290);
		param->wodt          = 1;
		param->rodt          = 1;
		param->reg_AC1       = 0x33302926;
		param->reg_AC2       = 0xEF44B61E;
		param->reg_DQSIC     = 0x00000125;
		param->reg_MRS       = 0x00081A30;
		param->reg_EMRS      = 0x00000040;
		param->reg_DRV       = 0x000000F5;
		param->reg_IOZ       = 0x00000023;
		param->reg_DQIDLY    = 0x00000088;
		param->reg_FREQ      = 0x000055C0;
		param->madj_max      = 76;
		param->dll2_finetune_step = 3;
		break;
	case 576:
		ast_moutdwm(ast, 0x1E6E2020, 0x0140);
		param->reg_MADJ      = 0x00136868;
		param->reg_SADJ      = 0x00004534;
		param->wodt          = 1;
		param->rodt          = 1;
		param->reg_AC1       = 0x33302A37;
		param->reg_AC2       = 0xEF56B61E;
		param->reg_DQSIC     = 0x0000013F;
		param->reg_MRS       = 0x00101A50;
		param->reg_EMRS      = 0x00000040;
		param->reg_DRV       = 0x000000FA;
		param->reg_IOZ       = 0x00000023;
		param->reg_DQIDLY    = 0x00000078;
		param->reg_FREQ      = 0x000057C0;
		param->madj_max      = 136;
		param->dll2_finetune_step = 3;
		break;
	case 600:
		ast_moutdwm(ast, 0x1E6E2020, 0x02E1);
		param->reg_MADJ      = 0x00136868;
		param->reg_SADJ      = 0x00004534;
		param->wodt          = 1;
		param->rodt          = 1;
		param->reg_AC1       = 0x32302A37;
		param->reg_AC2       = 0xDF56B61F;
		param->reg_DQSIC     = 0x0000014D;
		param->reg_MRS       = 0x00101A50;
		param->reg_EMRS      = 0x00000004;
		param->reg_DRV       = 0x000000F5;
		param->reg_IOZ       = 0x00000023;
		param->reg_DQIDLY    = 0x00000078;
		param->reg_FREQ      = 0x000058C0;
		param->madj_max      = 132;
		param->dll2_finetune_step = 3;
		break;
	case 624:
		ast_moutdwm(ast, 0x1E6E2020, 0x0160);
		param->reg_MADJ      = 0x00136868;
		param->reg_SADJ      = 0x00004534;
		param->wodt          = 1;
		param->rodt          = 1;
		param->reg_AC1       = 0x32302A37;
		param->reg_AC2       = 0xEF56B621;
		param->reg_DQSIC     = 0x0000015A;
		param->reg_MRS       = 0x02101A50;
		param->reg_EMRS      = 0x00000004;
		param->reg_DRV       = 0x000000F5;
		param->reg_IOZ       = 0x00000034;
		param->reg_DQIDLY    = 0x00000078;
		param->reg_FREQ      = 0x000059C0;
		param->madj_max      = 128;
		param->dll2_finetune_step = 3;
		break;
	} /* switch freq */

	switch (param->dram_chipid) {
	case AST_DRAM_512Mx16:
		param->dram_config = 0x130;
		break;
	default:
	case AST_DRAM_1Gx16:
		param->dram_config = 0x131;
		break;
	case AST_DRAM_2Gx16:
		param->dram_config = 0x132;
		break;
	case AST_DRAM_4Gx16:
		param->dram_config = 0x133;
		break;
	} /* switch size */

	switch (param->vram_size) {
	default:
	case AST_VIDMEM_SIZE_8M:
		param->dram_config |= 0x00;
		break;
	case AST_VIDMEM_SIZE_16M:
		param->dram_config |= 0x04;
		break;
	case AST_VIDMEM_SIZE_32M:
		param->dram_config |= 0x08;
		break;
	case AST_VIDMEM_SIZE_64M:
		param->dram_config |= 0x0c;
		break;
	}

}