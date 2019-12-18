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
 size_t REGIDX_010 ; 
 size_t REGIDX_014 ; 
 size_t REGIDX_018 ; 
 size_t REGIDX_020 ; 
 size_t REGIDX_024 ; 
 size_t REGIDX_02C ; 
 size_t REGIDX_030 ; 
 size_t REGIDX_214 ; 
 size_t REGIDX_2E0 ; 
 size_t REGIDX_2E4 ; 
 size_t REGIDX_2E8 ; 
 size_t REGIDX_2EC ; 
 size_t REGIDX_2F0 ; 
 size_t REGIDX_2F4 ; 
 size_t REGIDX_2F8 ; 
 size_t REGIDX_PLL ; 
 size_t REGIDX_RFC ; 
 int ast_mindwm (struct ast_private*,int) ; 
 int /*<<< orphan*/  ast_moutdwm (struct ast_private*,int,int const) ; 
 scalar_t__ cbr_test_2500 (struct ast_private*) ; 
 int /*<<< orphan*/  check_dram_size_2500 (struct ast_private*,int const) ; 
 int /*<<< orphan*/  ddr_phy_init_2500 (struct ast_private*) ; 
 int /*<<< orphan*/  enable_cache_2500 (struct ast_private*) ; 

__attribute__((used)) static void ddr4_init_2500(struct ast_private *ast, const u32 *ddr_table)
{
	u32 data, data2, pass, retrycnt;
	u32 ddr_vref, phy_vref;
	u32 min_ddr_vref = 0, min_phy_vref = 0;
	u32 max_ddr_vref = 0, max_phy_vref = 0;

	ast_moutdwm(ast, 0x1E6E0004, 0x00000313);
	ast_moutdwm(ast, 0x1E6E0010, ddr_table[REGIDX_010]);
	ast_moutdwm(ast, 0x1E6E0014, ddr_table[REGIDX_014]);
	ast_moutdwm(ast, 0x1E6E0018, ddr_table[REGIDX_018]);
	ast_moutdwm(ast, 0x1E6E0020, ddr_table[REGIDX_020]);	     /* MODEREG4/6 */
	ast_moutdwm(ast, 0x1E6E0024, ddr_table[REGIDX_024]);	     /* MODEREG5 */
	ast_moutdwm(ast, 0x1E6E002C, ddr_table[REGIDX_02C] | 0x100); /* MODEREG0/2 */
	ast_moutdwm(ast, 0x1E6E0030, ddr_table[REGIDX_030]);	     /* MODEREG1/3 */

	/* DDR PHY Setting */
	ast_moutdwm(ast, 0x1E6E0200, 0x42492AAE);
	ast_moutdwm(ast, 0x1E6E0204, 0x09002000);
	ast_moutdwm(ast, 0x1E6E020C, 0x55E00B0B);
	ast_moutdwm(ast, 0x1E6E0210, 0x20000000);
	ast_moutdwm(ast, 0x1E6E0214, ddr_table[REGIDX_214]);
	ast_moutdwm(ast, 0x1E6E02E0, ddr_table[REGIDX_2E0]);
	ast_moutdwm(ast, 0x1E6E02E4, ddr_table[REGIDX_2E4]);
	ast_moutdwm(ast, 0x1E6E02E8, ddr_table[REGIDX_2E8]);
	ast_moutdwm(ast, 0x1E6E02EC, ddr_table[REGIDX_2EC]);
	ast_moutdwm(ast, 0x1E6E02F0, ddr_table[REGIDX_2F0]);
	ast_moutdwm(ast, 0x1E6E02F4, ddr_table[REGIDX_2F4]);
	ast_moutdwm(ast, 0x1E6E02F8, ddr_table[REGIDX_2F8]);
	ast_moutdwm(ast, 0x1E6E0290, 0x00100008);
	ast_moutdwm(ast, 0x1E6E02C4, 0x3C183C3C);
	ast_moutdwm(ast, 0x1E6E02C8, 0x00631E0E);

	/* Controller Setting */
	ast_moutdwm(ast, 0x1E6E0034, 0x0001A991);

	/* Train PHY Vref first */
	pass = 0;

	for (retrycnt = 0; retrycnt < 4 && pass == 0; retrycnt++) {
		max_phy_vref = 0x0;
		pass = 0;
		ast_moutdwm(ast, 0x1E6E02C0, 0x00001C06);
		for (phy_vref = 0x40; phy_vref < 0x80; phy_vref++) {
			ast_moutdwm(ast, 0x1E6E000C, 0x00000000);
			ast_moutdwm(ast, 0x1E6E0060, 0x00000000);
			ast_moutdwm(ast, 0x1E6E02CC, phy_vref | (phy_vref << 8));
			/* Fire DFI Init */
			ddr_phy_init_2500(ast);
			ast_moutdwm(ast, 0x1E6E000C, 0x00005C01);
			if (cbr_test_2500(ast)) {
				pass++;
				data = ast_mindwm(ast, 0x1E6E03D0);
				data2 = data >> 8;
				data  = data & 0xff;
				if (data > data2)
					data = data2;
				if (max_phy_vref < data) {
					max_phy_vref = data;
					min_phy_vref = phy_vref;
				}
			} else if (pass > 0)
				break;
		}
	}
	ast_moutdwm(ast, 0x1E6E02CC, min_phy_vref | (min_phy_vref << 8));

	/* Train DDR Vref next */
	pass = 0;

	for (retrycnt = 0; retrycnt < 4 && pass == 0; retrycnt++) {
		min_ddr_vref = 0xFF;
		max_ddr_vref = 0x0;
		pass = 0;
		for (ddr_vref = 0x00; ddr_vref < 0x40; ddr_vref++) {
			ast_moutdwm(ast, 0x1E6E000C, 0x00000000);
			ast_moutdwm(ast, 0x1E6E0060, 0x00000000);
			ast_moutdwm(ast, 0x1E6E02C0, 0x00000006 | (ddr_vref << 8));
			/* Fire DFI Init */
			ddr_phy_init_2500(ast);
			ast_moutdwm(ast, 0x1E6E000C, 0x00005C01);
			if (cbr_test_2500(ast)) {
				pass++;
				if (min_ddr_vref > ddr_vref)
					min_ddr_vref = ddr_vref;
				if (max_ddr_vref < ddr_vref)
					max_ddr_vref = ddr_vref;
			} else if (pass != 0)
				break;
		}
	}

	ast_moutdwm(ast, 0x1E6E000C, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0060, 0x00000000);
	ddr_vref = (min_ddr_vref + max_ddr_vref + 1) >> 1;
	ast_moutdwm(ast, 0x1E6E02C0, 0x00000006 | (ddr_vref << 8));

	/* Wait DDR PHY init done */
	ddr_phy_init_2500(ast);

	ast_moutdwm(ast, 0x1E6E0120, ddr_table[REGIDX_PLL]);
	ast_moutdwm(ast, 0x1E6E000C, 0x42AA5C81);
	ast_moutdwm(ast, 0x1E6E0034, 0x0001AF93);

	check_dram_size_2500(ast, ddr_table[REGIDX_RFC]);
	enable_cache_2500(ast);
	ast_moutdwm(ast, 0x1E6E001C, 0x00000008);
	ast_moutdwm(ast, 0x1E6E0038, 0xFFFFFF00);
}