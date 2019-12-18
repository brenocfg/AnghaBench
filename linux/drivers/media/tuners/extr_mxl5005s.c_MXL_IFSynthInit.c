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
typedef  int /*<<< orphan*/  u16 ;
struct mxl5005s_state {unsigned long Fxtal; scalar_t__ Mode; int IF_Mode; unsigned long IF_LO; } ;
struct dvb_frontend {struct mxl5005s_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHCAL_FRAC_MOD_IF ; 
 int /*<<< orphan*/  CHCAL_INT_MOD_IF ; 
 int /*<<< orphan*/  IF_DIVVAL ; 
 int /*<<< orphan*/  IF_VCO_BIAS ; 
 scalar_t__ MXL_ControlWrite (struct dvb_frontend*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u16 MXL_IFSynthInit(struct dvb_frontend *fe)
{
	struct mxl5005s_state *state = fe->tuner_priv;
	u16 status = 0 ;
	u32	Fref = 0 ;
	u32	Kdbl, intModVal ;
	u32	fracModVal ;
	Kdbl = 2 ;

	if (state->Fxtal >= 12000000UL && state->Fxtal <= 16000000UL)
		Kdbl = 2 ;
	if (state->Fxtal > 16000000UL && state->Fxtal <= 32000000UL)
		Kdbl = 1 ;

	/* IF Synthesizer Control */
	if (state->Mode == 0 && state->IF_Mode == 1) /* Analog Low IF mode */ {
		if (state->IF_LO == 41000000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x0C);
			Fref = 328000000UL ;
		}
		if (state->IF_LO == 47000000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 376000000UL ;
		}
		if (state->IF_LO == 54000000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x10);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x0C);
			Fref = 324000000UL ;
		}
		if (state->IF_LO == 60000000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x10);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 360000000UL ;
		}
		if (state->IF_LO == 39250000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x0C);
			Fref = 314000000UL ;
		}
		if (state->IF_LO == 39650000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x0C);
			Fref = 317200000UL ;
		}
		if (state->IF_LO == 40150000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x0C);
			Fref = 321200000UL ;
		}
		if (state->IF_LO == 40650000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x0C);
			Fref = 325200000UL ;
		}
	}

	if (state->Mode || (state->Mode == 0 && state->IF_Mode == 0)) {
		if (state->IF_LO == 57000000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x10);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 342000000UL ;
		}
		if (state->IF_LO == 44000000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 352000000UL ;
		}
		if (state->IF_LO == 43750000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 350000000UL ;
		}
		if (state->IF_LO == 36650000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 366500000UL ;
		}
		if (state->IF_LO == 36150000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 361500000UL ;
		}
		if (state->IF_LO == 36000000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 360000000UL ;
		}
		if (state->IF_LO == 35250000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 352500000UL ;
		}
		if (state->IF_LO == 34750000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 347500000UL ;
		}
		if (state->IF_LO == 6280000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x07);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 376800000UL ;
		}
		if (state->IF_LO == 5000000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x09);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 360000000UL ;
		}
		if (state->IF_LO == 4500000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x06);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 360000000UL ;
		}
		if (state->IF_LO == 4570000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x06);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 365600000UL ;
		}
		if (state->IF_LO == 4000000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x05);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 360000000UL ;
		}
		if (state->IF_LO == 57400000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x10);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 344400000UL ;
		}
		if (state->IF_LO == 44400000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 355200000UL ;
		}
		if (state->IF_LO == 44150000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x08);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 353200000UL ;
		}
		if (state->IF_LO == 37050000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 370500000UL ;
		}
		if (state->IF_LO == 36550000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 365500000UL ;
		}
		if (state->IF_LO == 36125000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x04);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 361250000UL ;
		}
		if (state->IF_LO == 6000000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x07);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 360000000UL ;
		}
		if (state->IF_LO == 5400000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x07);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x0C);
			Fref = 324000000UL ;
		}
		if (state->IF_LO == 5380000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x07);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x0C);
			Fref = 322800000UL ;
		}
		if (state->IF_LO == 5200000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x09);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 374400000UL ;
		}
		if (state->IF_LO == 4900000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x09);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 352800000UL ;
		}
		if (state->IF_LO == 4400000UL) {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x06);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 352000000UL ;
		}
		if (state->IF_LO == 4063000UL)  /* add for 2.6.8 */ {
			status += MXL_ControlWrite(fe, IF_DIVVAL,   0x05);
			status += MXL_ControlWrite(fe, IF_VCO_BIAS, 0x08);
			Fref = 365670000UL ;
		}
	}
	/* CHCAL_INT_MOD_IF */
	/* CHCAL_FRAC_MOD_IF */
	intModVal = Fref / (state->Fxtal * Kdbl/2);
	status += MXL_ControlWrite(fe, CHCAL_INT_MOD_IF, intModVal);

	fracModVal = (2<<15)*(Fref/1000 - (state->Fxtal/1000 * Kdbl/2) *
		intModVal);

	fracModVal = fracModVal / ((state->Fxtal * Kdbl/2)/1000);
	status += MXL_ControlWrite(fe, CHCAL_FRAC_MOD_IF, fracModVal);

	return status ;
}