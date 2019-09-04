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

/* Variables and functions */
 int /*<<< orphan*/  DDR0_02 ; 
 int /*<<< orphan*/  DDR0_14 ; 
 int /*<<< orphan*/  DDR0_42 ; 
 int /*<<< orphan*/  DDR0_43 ; 
 int /*<<< orphan*/  DDR_APIN ; 
 int /*<<< orphan*/  DDR_APIN_SHIFT ; 
 int /*<<< orphan*/  DDR_BANK8 ; 
 int /*<<< orphan*/  DDR_BANK8_SHIFT ; 
 int /*<<< orphan*/  DDR_COL_SZ ; 
 int /*<<< orphan*/  DDR_COL_SZ_SHIFT ; 
 int DDR_GET_VAL (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DDR_MAX_COL_REG ; 
 int /*<<< orphan*/  DDR_MAX_COL_REG_SHIFT ; 
 int /*<<< orphan*/  DDR_MAX_CS_REG ; 
 int /*<<< orphan*/  DDR_MAX_CS_REG_SHIFT ; 
 int /*<<< orphan*/  DDR_MAX_ROW_REG ; 
 int /*<<< orphan*/  DDR_MAX_ROW_REG_SHIFT ; 
 int /*<<< orphan*/  DDR_REDUC ; 
 int /*<<< orphan*/  DDR_REDUC_SHIFT ; 
 int /*<<< orphan*/  DDR_START ; 
 int /*<<< orphan*/  DDR_START_SHIFT ; 
 int SDRAM0_READ (int /*<<< orphan*/ ) ; 
 unsigned long chip_11_errata (unsigned long) ; 
 int /*<<< orphan*/  dt_fixup_memory (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int ibm4xx_denali_get_cs () ; 

void ibm4xx_denali_fixup_memsize(void)
{
	u32 val, max_cs, max_col, max_row;
	u32 cs, col, row, bank, dpath;
	unsigned long memsize;

	val = SDRAM0_READ(DDR0_02);
	if (!DDR_GET_VAL(val, DDR_START, DDR_START_SHIFT))
		fatal("DDR controller is not initialized\n");

	/* get maximum cs col and row values */
	max_cs  = DDR_GET_VAL(val, DDR_MAX_CS_REG, DDR_MAX_CS_REG_SHIFT);
	max_col = DDR_GET_VAL(val, DDR_MAX_COL_REG, DDR_MAX_COL_REG_SHIFT);
	max_row = DDR_GET_VAL(val, DDR_MAX_ROW_REG, DDR_MAX_ROW_REG_SHIFT);

	cs = ibm4xx_denali_get_cs();
	if (!cs)
		fatal("No memory installed\n");
	if (cs > max_cs)
		fatal("DDR wrong CS configuration\n");

	/* get data path bytes */
	val = SDRAM0_READ(DDR0_14);

	if (DDR_GET_VAL(val, DDR_REDUC, DDR_REDUC_SHIFT))
		dpath = 4; /* 32 bits */
	else
		dpath = 8; /* 64 bits */

	/* get address pins (rows) */
 	val = SDRAM0_READ(DDR0_42);

	row = DDR_GET_VAL(val, DDR_APIN, DDR_APIN_SHIFT);
	if (row > max_row)
		fatal("DDR wrong APIN configuration\n");
	row = max_row - row;

	/* get collomn size and banks */
	val = SDRAM0_READ(DDR0_43);

	col = DDR_GET_VAL(val, DDR_COL_SZ, DDR_COL_SZ_SHIFT);
	if (col > max_col)
		fatal("DDR wrong COL configuration\n");
	col = max_col - col;

	if (DDR_GET_VAL(val, DDR_BANK8, DDR_BANK8_SHIFT))
		bank = 8; /* 8 banks */
	else
		bank = 4; /* 4 banks */

	memsize = cs * (1 << (col+row)) * bank * dpath;
	memsize = chip_11_errata(memsize);
	dt_fixup_memory(0, memsize);
}