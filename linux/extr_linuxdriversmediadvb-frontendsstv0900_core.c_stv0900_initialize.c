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
struct stv0900_internal {int chip_id; scalar_t__ errs; int clkmode; } ;
typedef  int s32 ;
typedef  enum fe_stv0900_error { ____Placeholder_fe_stv0900_error } fe_stv0900_error ;

/* Variables and functions */
 int R0900_I2CCFG ; 
 int R0900_MID ; 
 int R0900_NCOARSE ; 
 int R0900_P1_DMDISTATE ; 
 int R0900_P1_FSPYCFG ; 
 int R0900_P1_I2CRPT ; 
 int R0900_P1_PDELCTRL2 ; 
 int R0900_P1_PDELCTRL3 ; 
 int R0900_P1_TNRCFG ; 
 int R0900_P2_DMDISTATE ; 
 int R0900_P2_FSPYCFG ; 
 int R0900_P2_I2CRPT ; 
 int R0900_P2_PDELCTRL2 ; 
 int R0900_P2_PDELCTRL3 ; 
 int R0900_P2_TNRCFG ; 
 int R0900_SYNTCTRL ; 
 int R0900_TSGENERAL ; 
 int R0900_TSTRES0 ; 
 int** STV0900_Cut20_AddOnVal ; 
 int STV0900_INVALID_HANDLE ; 
 int** STV0900_InitVal ; 
 scalar_t__ STV0900_NO_ERROR ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stv0900_read_reg (struct stv0900_internal*,int) ; 
 int /*<<< orphan*/  stv0900_write_reg (struct stv0900_internal*,int,int) ; 

__attribute__((used)) static enum fe_stv0900_error stv0900_initialize(struct stv0900_internal *intp)
{
	s32 i;

	if (intp == NULL)
		return STV0900_INVALID_HANDLE;

	intp->chip_id = stv0900_read_reg(intp, R0900_MID);

	if (intp->errs != STV0900_NO_ERROR)
		return intp->errs;

	/*Startup sequence*/
	stv0900_write_reg(intp, R0900_P1_DMDISTATE, 0x5c);
	stv0900_write_reg(intp, R0900_P2_DMDISTATE, 0x5c);
	msleep(3);
	stv0900_write_reg(intp, R0900_P1_TNRCFG, 0x6c);
	stv0900_write_reg(intp, R0900_P2_TNRCFG, 0x6f);
	stv0900_write_reg(intp, R0900_P1_I2CRPT, 0x20);
	stv0900_write_reg(intp, R0900_P2_I2CRPT, 0x20);
	stv0900_write_reg(intp, R0900_NCOARSE, 0x13);
	msleep(3);
	stv0900_write_reg(intp, R0900_I2CCFG, 0x08);

	switch (intp->clkmode) {
	case 0:
	case 2:
		stv0900_write_reg(intp, R0900_SYNTCTRL, 0x20
				| intp->clkmode);
		break;
	default:
		/* preserve SELOSCI bit */
		i = 0x02 & stv0900_read_reg(intp, R0900_SYNTCTRL);
		stv0900_write_reg(intp, R0900_SYNTCTRL, 0x20 | i);
		break;
	}

	msleep(3);
	for (i = 0; i < 181; i++)
		stv0900_write_reg(intp, STV0900_InitVal[i][0],
				STV0900_InitVal[i][1]);

	if (stv0900_read_reg(intp, R0900_MID) >= 0x20) {
		stv0900_write_reg(intp, R0900_TSGENERAL, 0x0c);
		for (i = 0; i < 32; i++)
			stv0900_write_reg(intp, STV0900_Cut20_AddOnVal[i][0],
					STV0900_Cut20_AddOnVal[i][1]);
	}

	stv0900_write_reg(intp, R0900_P1_FSPYCFG, 0x6c);
	stv0900_write_reg(intp, R0900_P2_FSPYCFG, 0x6c);

	stv0900_write_reg(intp, R0900_P1_PDELCTRL2, 0x01);
	stv0900_write_reg(intp, R0900_P2_PDELCTRL2, 0x21);

	stv0900_write_reg(intp, R0900_P1_PDELCTRL3, 0x20);
	stv0900_write_reg(intp, R0900_P2_PDELCTRL3, 0x20);

	stv0900_write_reg(intp, R0900_TSTRES0, 0x80);
	stv0900_write_reg(intp, R0900_TSTRES0, 0x00);

	return STV0900_NO_ERROR;
}