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
struct mt2063_state {int* reg; int rcvr_mode; } ;
typedef  enum mt2063_delivery_sys { ____Placeholder_mt2063_delivery_sys } mt2063_delivery_sys ;

/* Variables and functions */
 int* ACFIFMAX ; 
 int* ACLNAMAX ; 
 int* ACRFMAX ; 
 int ERANGE ; 
 int* FIFFQ ; 
 int* FIFFQEN ; 
 scalar_t__* FIFOVDIS ; 
 int* LNARIN ; 
 int* LNATGT ; 
 int MT2063_B3 ; 
 int MT2063_NUM_RCVR_MODES ; 
 size_t MT2063_REG_CTRL_2C ; 
 size_t MT2063_REG_FIFF_CTRL ; 
 size_t MT2063_REG_FIFF_CTRL2 ; 
 size_t MT2063_REG_FIF_OV ; 
 size_t MT2063_REG_LNA_OV ; 
 size_t MT2063_REG_LNA_TGT ; 
 size_t MT2063_REG_PART_REV ; 
 size_t MT2063_REG_PD1_TGT ; 
 size_t MT2063_REG_PD2_TGT ; 
 size_t MT2063_REG_RF_OV ; 
 int* PD1TGT ; 
 int* PD2TGT ; 
 scalar_t__* RFAGCEN ; 
 scalar_t__* RFOVDIS ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int mt2063_get_dnc_output_enable (struct mt2063_state*,int*) ; 
 int /*<<< orphan*/ * mt2063_mode_name ; 
 int mt2063_set_dnc_output_enable (struct mt2063_state*,int) ; 
 int mt2063_setreg (struct mt2063_state*,size_t,int) ; 

__attribute__((used)) static u32 MT2063_SetReceiverMode(struct mt2063_state *state,
				  enum mt2063_delivery_sys Mode)
{
	int status = 0;	/* Status to be returned        */
	u8 val;
	u32 longval;

	dprintk(2, "\n");

	if (Mode >= MT2063_NUM_RCVR_MODES)
		status = -ERANGE;

	/* RFAGCen */
	if (status >= 0) {
		val =
		    (state->
		     reg[MT2063_REG_PD1_TGT] & ~0x40) | (RFAGCEN[Mode]
								   ? 0x40 :
								   0x00);
		if (state->reg[MT2063_REG_PD1_TGT] != val)
			status |= mt2063_setreg(state, MT2063_REG_PD1_TGT, val);
	}

	/* LNARin */
	if (status >= 0) {
		u8 val = (state->reg[MT2063_REG_CTRL_2C] & ~0x03) |
			 (LNARIN[Mode] & 0x03);
		if (state->reg[MT2063_REG_CTRL_2C] != val)
			status |= mt2063_setreg(state, MT2063_REG_CTRL_2C, val);
	}

	/* FIFFQEN and FIFFQ */
	if (status >= 0) {
		val =
		    (state->
		     reg[MT2063_REG_FIFF_CTRL2] & ~0xF0) |
		    (FIFFQEN[Mode] << 7) | (FIFFQ[Mode] << 4);
		if (state->reg[MT2063_REG_FIFF_CTRL2] != val) {
			status |=
			    mt2063_setreg(state, MT2063_REG_FIFF_CTRL2, val);
			/* trigger FIFF calibration, needed after changing FIFFQ */
			val =
			    (state->reg[MT2063_REG_FIFF_CTRL] | 0x01);
			status |=
			    mt2063_setreg(state, MT2063_REG_FIFF_CTRL, val);
			val =
			    (state->
			     reg[MT2063_REG_FIFF_CTRL] & ~0x01);
			status |=
			    mt2063_setreg(state, MT2063_REG_FIFF_CTRL, val);
		}
	}

	/* DNC1GC & DNC2GC */
	status |= mt2063_get_dnc_output_enable(state, &longval);
	status |= mt2063_set_dnc_output_enable(state, longval);

	/* acLNAmax */
	if (status >= 0) {
		u8 val = (state->reg[MT2063_REG_LNA_OV] & ~0x1F) |
			 (ACLNAMAX[Mode] & 0x1F);
		if (state->reg[MT2063_REG_LNA_OV] != val)
			status |= mt2063_setreg(state, MT2063_REG_LNA_OV, val);
	}

	/* LNATGT */
	if (status >= 0) {
		u8 val = (state->reg[MT2063_REG_LNA_TGT] & ~0x3F) |
			 (LNATGT[Mode] & 0x3F);
		if (state->reg[MT2063_REG_LNA_TGT] != val)
			status |= mt2063_setreg(state, MT2063_REG_LNA_TGT, val);
	}

	/* ACRF */
	if (status >= 0) {
		u8 val = (state->reg[MT2063_REG_RF_OV] & ~0x1F) |
			 (ACRFMAX[Mode] & 0x1F);
		if (state->reg[MT2063_REG_RF_OV] != val)
			status |= mt2063_setreg(state, MT2063_REG_RF_OV, val);
	}

	/* PD1TGT */
	if (status >= 0) {
		u8 val = (state->reg[MT2063_REG_PD1_TGT] & ~0x3F) |
			 (PD1TGT[Mode] & 0x3F);
		if (state->reg[MT2063_REG_PD1_TGT] != val)
			status |= mt2063_setreg(state, MT2063_REG_PD1_TGT, val);
	}

	/* FIFATN */
	if (status >= 0) {
		u8 val = ACFIFMAX[Mode];
		if (state->reg[MT2063_REG_PART_REV] != MT2063_B3 && val > 5)
			val = 5;
		val = (state->reg[MT2063_REG_FIF_OV] & ~0x1F) |
		      (val & 0x1F);
		if (state->reg[MT2063_REG_FIF_OV] != val)
			status |= mt2063_setreg(state, MT2063_REG_FIF_OV, val);
	}

	/* PD2TGT */
	if (status >= 0) {
		u8 val = (state->reg[MT2063_REG_PD2_TGT] & ~0x3F) |
		    (PD2TGT[Mode] & 0x3F);
		if (state->reg[MT2063_REG_PD2_TGT] != val)
			status |= mt2063_setreg(state, MT2063_REG_PD2_TGT, val);
	}

	/* Ignore ATN Overload */
	if (status >= 0) {
		val = (state->reg[MT2063_REG_LNA_TGT] & ~0x80) |
		      (RFOVDIS[Mode] ? 0x80 : 0x00);
		if (state->reg[MT2063_REG_LNA_TGT] != val)
			status |= mt2063_setreg(state, MT2063_REG_LNA_TGT, val);
	}

	/* Ignore FIF Overload */
	if (status >= 0) {
		val = (state->reg[MT2063_REG_PD1_TGT] & ~0x80) |
		      (FIFOVDIS[Mode] ? 0x80 : 0x00);
		if (state->reg[MT2063_REG_PD1_TGT] != val)
			status |= mt2063_setreg(state, MT2063_REG_PD1_TGT, val);
	}

	if (status >= 0) {
		state->rcvr_mode = Mode;
		dprintk(1, "mt2063 mode changed to %s\n",
			mt2063_mode_name[state->rcvr_mode]);
	}

	return status;
}