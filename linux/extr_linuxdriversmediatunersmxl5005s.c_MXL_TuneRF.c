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
typedef  int u32 ;
typedef  int u16 ;
struct mxl5005s_state {int RF_IN; unsigned long Fxtal; unsigned long RF_LO; unsigned long TG_LO; scalar_t__ Mod_Type; scalar_t__ TF_Type; TYPE_1__* config; } ;
struct dvb_frontend {struct mxl5005s_state* tuner_priv; } ;
struct TYPE_2__ {int qam_gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC_EN_RSSI ; 
 int /*<<< orphan*/  AGC_IF ; 
 int /*<<< orphan*/  CHCAL_EN_INT_RF ; 
 int /*<<< orphan*/  CHCAL_FRAC_MOD_RF ; 
 int /*<<< orphan*/  CHCAL_INT_MOD_RF ; 
 int /*<<< orphan*/  DAC_A_ENABLE ; 
 int /*<<< orphan*/  DAC_B_ENABLE ; 
 int /*<<< orphan*/  DAC_DIN_A ; 
 int /*<<< orphan*/  DAC_DIN_B ; 
 int /*<<< orphan*/  DN_CAP_RFLPF ; 
 int /*<<< orphan*/  DN_EN_VHFUHFBAR ; 
 int /*<<< orphan*/  DN_GAIN_ADJUST ; 
 int /*<<< orphan*/  DN_IQTNBUF_AMP ; 
 int /*<<< orphan*/  DN_IQTNGNBFBIAS_BST ; 
 int /*<<< orphan*/  DN_POLY ; 
 int /*<<< orphan*/  DN_RFGAIN ; 
 int /*<<< orphan*/  DN_SEL_FREQ ; 
 int MXL_Ceiling (int,int) ; 
 scalar_t__ MXL_ControlWrite (struct dvb_frontend*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MXL_QAM ; 
 scalar_t__ MXL_SetGPIO (struct dvb_frontend*,int,int) ; 
 int /*<<< orphan*/  MXL_SynthRFTGLO_Calc (struct dvb_frontend*) ; 
 scalar_t__ MXL_TF_C ; 
 scalar_t__ MXL_TF_C_H ; 
 scalar_t__ MXL_TF_D ; 
 scalar_t__ MXL_TF_D_L ; 
 scalar_t__ MXL_TF_E ; 
 scalar_t__ MXL_TF_E_2 ; 
 scalar_t__ MXL_TF_E_NA ; 
 scalar_t__ MXL_TF_F ; 
 scalar_t__ MXL_TF_G ; 
 scalar_t__ MXL_TF_OFF ; 
 int /*<<< orphan*/  RFA_ENCLKRFAGC ; 
 int /*<<< orphan*/  RFA_RSSI_REF ; 
 int /*<<< orphan*/  RFA_RSSI_REFH ; 
 int /*<<< orphan*/  RFA_RSSI_REFL ; 
 int /*<<< orphan*/  RFSYN_CHP_GAIN ; 
 int /*<<< orphan*/  RFSYN_EN_OUTMUX ; 
 int /*<<< orphan*/  RFSYN_LPF_R ; 
 int /*<<< orphan*/  RFSYN_RF_DIV_BIAS ; 
 int /*<<< orphan*/  RFSYN_SEL_DIVM ; 
 int /*<<< orphan*/  RFSYN_SEL_VCO_HI ; 
 int /*<<< orphan*/  RFSYN_SEL_VCO_OUT ; 
 int /*<<< orphan*/  RFSYN_VCO_BIAS ; 
 int /*<<< orphan*/  SEQ_EXTDCCAL ; 
 int /*<<< orphan*/  SEQ_EXTSYNTHCALIF ; 
 int /*<<< orphan*/  TG_DIV_VAL ; 
 int /*<<< orphan*/  TG_LO_DIVVAL ; 
 int /*<<< orphan*/  TG_LO_SELVAL ; 
 int /*<<< orphan*/  TG_VCO_BIAS ; 

__attribute__((used)) static u16 MXL_TuneRF(struct dvb_frontend *fe, u32 RF_Freq)
{
	struct mxl5005s_state *state = fe->tuner_priv;
	u16 status = 0;
	u32 divider_val, E3, E4, E5, E5A;
	u32 Fmax, Fmin, FmaxBin, FminBin;
	u32 Kdbl_RF = 2;
	u32 tg_divval;
	u32 tg_lo;

	u32 Fref_TG;
	u32 Fvco;

	state->RF_IN = RF_Freq;

	MXL_SynthRFTGLO_Calc(fe);

	if (state->Fxtal >= 12000000UL && state->Fxtal <= 22000000UL)
		Kdbl_RF = 2;
	if (state->Fxtal > 22000000 && state->Fxtal <= 32000000)
		Kdbl_RF = 1;

	/* Downconverter Controls
	 * Look-Up Table Implementation for:
	 *	DN_POLY
	 *	DN_RFGAIN
	 *	DN_CAP_RFLPF
	 *	DN_EN_VHFUHFBAR
	 *	DN_GAIN_ADJUST
	 *  Change the boundary reference from RF_IN to RF_LO
	 */
	if (state->RF_LO < 40000000UL)
		return -1;

	if (state->RF_LO >= 40000000UL && state->RF_LO <= 75000000UL) {
		status += MXL_ControlWrite(fe, DN_POLY,              2);
		status += MXL_ControlWrite(fe, DN_RFGAIN,            3);
		status += MXL_ControlWrite(fe, DN_CAP_RFLPF,         423);
		status += MXL_ControlWrite(fe, DN_EN_VHFUHFBAR,      1);
		status += MXL_ControlWrite(fe, DN_GAIN_ADJUST,       1);
	}
	if (state->RF_LO > 75000000UL && state->RF_LO <= 100000000UL) {
		status += MXL_ControlWrite(fe, DN_POLY,              3);
		status += MXL_ControlWrite(fe, DN_RFGAIN,            3);
		status += MXL_ControlWrite(fe, DN_CAP_RFLPF,         222);
		status += MXL_ControlWrite(fe, DN_EN_VHFUHFBAR,      1);
		status += MXL_ControlWrite(fe, DN_GAIN_ADJUST,       1);
	}
	if (state->RF_LO > 100000000UL && state->RF_LO <= 150000000UL) {
		status += MXL_ControlWrite(fe, DN_POLY,              3);
		status += MXL_ControlWrite(fe, DN_RFGAIN,            3);
		status += MXL_ControlWrite(fe, DN_CAP_RFLPF,         147);
		status += MXL_ControlWrite(fe, DN_EN_VHFUHFBAR,      1);
		status += MXL_ControlWrite(fe, DN_GAIN_ADJUST,       2);
	}
	if (state->RF_LO > 150000000UL && state->RF_LO <= 200000000UL) {
		status += MXL_ControlWrite(fe, DN_POLY,              3);
		status += MXL_ControlWrite(fe, DN_RFGAIN,            3);
		status += MXL_ControlWrite(fe, DN_CAP_RFLPF,         9);
		status += MXL_ControlWrite(fe, DN_EN_VHFUHFBAR,      1);
		status += MXL_ControlWrite(fe, DN_GAIN_ADJUST,       2);
	}
	if (state->RF_LO > 200000000UL && state->RF_LO <= 300000000UL) {
		status += MXL_ControlWrite(fe, DN_POLY,              3);
		status += MXL_ControlWrite(fe, DN_RFGAIN,            3);
		status += MXL_ControlWrite(fe, DN_CAP_RFLPF,         0);
		status += MXL_ControlWrite(fe, DN_EN_VHFUHFBAR,      1);
		status += MXL_ControlWrite(fe, DN_GAIN_ADJUST,       3);
	}
	if (state->RF_LO > 300000000UL && state->RF_LO <= 650000000UL) {
		status += MXL_ControlWrite(fe, DN_POLY,              3);
		status += MXL_ControlWrite(fe, DN_RFGAIN,            1);
		status += MXL_ControlWrite(fe, DN_CAP_RFLPF,         0);
		status += MXL_ControlWrite(fe, DN_EN_VHFUHFBAR,      0);
		status += MXL_ControlWrite(fe, DN_GAIN_ADJUST,       3);
	}
	if (state->RF_LO > 650000000UL && state->RF_LO <= 900000000UL) {
		status += MXL_ControlWrite(fe, DN_POLY,              3);
		status += MXL_ControlWrite(fe, DN_RFGAIN,            2);
		status += MXL_ControlWrite(fe, DN_CAP_RFLPF,         0);
		status += MXL_ControlWrite(fe, DN_EN_VHFUHFBAR,      0);
		status += MXL_ControlWrite(fe, DN_GAIN_ADJUST,       3);
	}
	if (state->RF_LO > 900000000UL)
		return -1;

	/*	DN_IQTNBUF_AMP */
	/*	DN_IQTNGNBFBIAS_BST */
	if (state->RF_LO >= 40000000UL && state->RF_LO <= 75000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 75000000UL && state->RF_LO <= 100000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 100000000UL && state->RF_LO <= 150000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 150000000UL && state->RF_LO <= 200000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 200000000UL && state->RF_LO <= 300000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 300000000UL && state->RF_LO <= 400000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 400000000UL && state->RF_LO <= 450000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 450000000UL && state->RF_LO <= 500000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 500000000UL && state->RF_LO <= 550000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 550000000UL && state->RF_LO <= 600000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 600000000UL && state->RF_LO <= 650000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 650000000UL && state->RF_LO <= 700000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 700000000UL && state->RF_LO <= 750000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 750000000UL && state->RF_LO <= 800000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       1);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  0);
	}
	if (state->RF_LO > 800000000UL && state->RF_LO <= 850000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       10);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  1);
	}
	if (state->RF_LO > 850000000UL && state->RF_LO <= 900000000UL) {
		status += MXL_ControlWrite(fe, DN_IQTNBUF_AMP,       10);
		status += MXL_ControlWrite(fe, DN_IQTNGNBFBIAS_BST,  1);
	}

	/*
	 * Set RF Synth and LO Path Control
	 *
	 * Look-Up table implementation for:
	 *	RFSYN_EN_OUTMUX
	 *	RFSYN_SEL_VCO_OUT
	 *	RFSYN_SEL_VCO_HI
	 *  RFSYN_SEL_DIVM
	 *	RFSYN_RF_DIV_BIAS
	 *	DN_SEL_FREQ
	 *
	 * Set divider_val, Fmax, Fmix to use in Equations
	 */
	FminBin = 28000000UL ;
	FmaxBin = 42500000UL ;
	if (state->RF_LO >= 40000000UL && state->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, RFSYN_EN_OUTMUX,     1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_OUT,   0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_HI,    0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(fe, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(fe, DN_SEL_FREQ,         1);
		divider_val = 64 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 42500000UL ;
	FmaxBin = 56000000UL ;
	if (state->RF_LO > FminBin && state->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, RFSYN_EN_OUTMUX,     1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_OUT,   0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_HI,    1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(fe, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(fe, DN_SEL_FREQ,         1);
		divider_val = 64 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 56000000UL ;
	FmaxBin = 85000000UL ;
	if (state->RF_LO > FminBin && state->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_HI,    0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(fe, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(fe, DN_SEL_FREQ,         1);
		divider_val = 32 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 85000000UL ;
	FmaxBin = 112000000UL ;
	if (state->RF_LO > FminBin && state->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_HI,    1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(fe, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(fe, DN_SEL_FREQ,         1);
		divider_val = 32 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 112000000UL ;
	FmaxBin = 170000000UL ;
	if (state->RF_LO > FminBin && state->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_HI,    0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(fe, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(fe, DN_SEL_FREQ,         2);
		divider_val = 16 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 170000000UL ;
	FmaxBin = 225000000UL ;
	if (state->RF_LO > FminBin && state->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_HI,    1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(fe, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(fe, DN_SEL_FREQ,         2);
		divider_val = 16 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 225000000UL ;
	FmaxBin = 300000000UL ;
	if (state->RF_LO > FminBin && state->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_HI,    0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(fe, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(fe, DN_SEL_FREQ,         4);
		divider_val = 8 ;
		Fmax = 340000000UL ;
		Fmin = FminBin ;
	}
	FminBin = 300000000UL ;
	FmaxBin = 340000000UL ;
	if (state->RF_LO > FminBin && state->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, RFSYN_EN_OUTMUX,     1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_OUT,   0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_HI,    0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(fe, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(fe, DN_SEL_FREQ,         0);
		divider_val = 8 ;
		Fmax = FmaxBin ;
		Fmin = 225000000UL ;
	}
	FminBin = 340000000UL ;
	FmaxBin = 450000000UL ;
	if (state->RF_LO > FminBin && state->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, RFSYN_EN_OUTMUX,     1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_OUT,   0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_HI,    1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_DIVM,      0);
		status += MXL_ControlWrite(fe, RFSYN_RF_DIV_BIAS,   2);
		status += MXL_ControlWrite(fe, DN_SEL_FREQ,         0);
		divider_val = 8 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 450000000UL ;
	FmaxBin = 680000000UL ;
	if (state->RF_LO > FminBin && state->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_HI,    0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_DIVM,      1);
		status += MXL_ControlWrite(fe, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(fe, DN_SEL_FREQ,         0);
		divider_val = 4 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 680000000UL ;
	FmaxBin = 900000000UL ;
	if (state->RF_LO > FminBin && state->RF_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, RFSYN_EN_OUTMUX,     0);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_OUT,   1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_VCO_HI,    1);
		status += MXL_ControlWrite(fe, RFSYN_SEL_DIVM,      1);
		status += MXL_ControlWrite(fe, RFSYN_RF_DIV_BIAS,   1);
		status += MXL_ControlWrite(fe, DN_SEL_FREQ,         0);
		divider_val = 4 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}

	/*	CHCAL_INT_MOD_RF
	 *	CHCAL_FRAC_MOD_RF
	 *	RFSYN_LPF_R
	 *	CHCAL_EN_INT_RF
	 */
	/* Equation E3 RFSYN_VCO_BIAS */
	E3 = (((Fmax-state->RF_LO)/1000)*32)/((Fmax-Fmin)/1000) + 8 ;
	status += MXL_ControlWrite(fe, RFSYN_VCO_BIAS, E3);

	/* Equation E4 CHCAL_INT_MOD_RF */
	E4 = (state->RF_LO*divider_val/1000)/(2*state->Fxtal*Kdbl_RF/1000);
	MXL_ControlWrite(fe, CHCAL_INT_MOD_RF, E4);

	/* Equation E5 CHCAL_FRAC_MOD_RF CHCAL_EN_INT_RF */
	E5 = ((2<<17)*(state->RF_LO/10000*divider_val -
		(E4*(2*state->Fxtal*Kdbl_RF)/10000))) /
		(2*state->Fxtal*Kdbl_RF/10000);

	status += MXL_ControlWrite(fe, CHCAL_FRAC_MOD_RF, E5);

	/* Equation E5A RFSYN_LPF_R */
	E5A = (((Fmax - state->RF_LO)/1000)*4/((Fmax-Fmin)/1000)) + 1 ;
	status += MXL_ControlWrite(fe, RFSYN_LPF_R, E5A);

	/* Euqation E5B CHCAL_EN_INIT_RF */
	status += MXL_ControlWrite(fe, CHCAL_EN_INT_RF, ((E5 == 0) ? 1 : 0));
	/*if (E5 == 0)
	 *	status += MXL_ControlWrite(fe, CHCAL_EN_INT_RF, 1);
	 *else
	 *	status += MXL_ControlWrite(fe, CHCAL_FRAC_MOD_RF, E5);
	 */

	/*
	 * Set TG Synth
	 *
	 * Look-Up table implementation for:
	 *	TG_LO_DIVVAL
	 *	TG_LO_SELVAL
	 *
	 * Set divider_val, Fmax, Fmix to use in Equations
	 */
	if (state->TG_LO < 33000000UL)
		return -1;

	FminBin = 33000000UL ;
	FmaxBin = 50000000UL ;
	if (state->TG_LO >= FminBin && state->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, TG_LO_DIVVAL,	0x6);
		status += MXL_ControlWrite(fe, TG_LO_SELVAL,	0x0);
		divider_val = 36 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 50000000UL ;
	FmaxBin = 67000000UL ;
	if (state->TG_LO > FminBin && state->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, TG_LO_DIVVAL,	0x1);
		status += MXL_ControlWrite(fe, TG_LO_SELVAL,	0x0);
		divider_val = 24 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 67000000UL ;
	FmaxBin = 100000000UL ;
	if (state->TG_LO > FminBin && state->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, TG_LO_DIVVAL,	0xC);
		status += MXL_ControlWrite(fe, TG_LO_SELVAL,	0x2);
		divider_val = 18 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 100000000UL ;
	FmaxBin = 150000000UL ;
	if (state->TG_LO > FminBin && state->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, TG_LO_DIVVAL,	0x8);
		status += MXL_ControlWrite(fe, TG_LO_SELVAL,	0x2);
		divider_val = 12 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 150000000UL ;
	FmaxBin = 200000000UL ;
	if (state->TG_LO > FminBin && state->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, TG_LO_DIVVAL,	0x0);
		status += MXL_ControlWrite(fe, TG_LO_SELVAL,	0x2);
		divider_val = 8 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 200000000UL ;
	FmaxBin = 300000000UL ;
	if (state->TG_LO > FminBin && state->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, TG_LO_DIVVAL,	0x8);
		status += MXL_ControlWrite(fe, TG_LO_SELVAL,	0x3);
		divider_val = 6 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 300000000UL ;
	FmaxBin = 400000000UL ;
	if (state->TG_LO > FminBin && state->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, TG_LO_DIVVAL,	0x0);
		status += MXL_ControlWrite(fe, TG_LO_SELVAL,	0x3);
		divider_val = 4 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 400000000UL ;
	FmaxBin = 600000000UL ;
	if (state->TG_LO > FminBin && state->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, TG_LO_DIVVAL,	0x8);
		status += MXL_ControlWrite(fe, TG_LO_SELVAL,	0x7);
		divider_val = 3 ;
		Fmax = FmaxBin ;
		Fmin = FminBin ;
	}
	FminBin = 600000000UL ;
	FmaxBin = 900000000UL ;
	if (state->TG_LO > FminBin && state->TG_LO <= FmaxBin) {
		status += MXL_ControlWrite(fe, TG_LO_DIVVAL,	0x0);
		status += MXL_ControlWrite(fe, TG_LO_SELVAL,	0x7);
		divider_val = 2 ;
	}

	/* TG_DIV_VAL */
	tg_divval = (state->TG_LO*divider_val/100000) *
		(MXL_Ceiling(state->Fxtal, 1000000) * 100) /
		(state->Fxtal/1000);

	status += MXL_ControlWrite(fe, TG_DIV_VAL, tg_divval);

	if (state->TG_LO > 600000000UL)
		status += MXL_ControlWrite(fe, TG_DIV_VAL, tg_divval + 1);

	Fmax = 1800000000UL ;
	Fmin = 1200000000UL ;

	/* prevent overflow of 32 bit unsigned integer, use
	 * following equation. Edit for v2.6.4
	 */
	/* Fref_TF = Fref_TG * 1000 */
	Fref_TG = (state->Fxtal/1000) / MXL_Ceiling(state->Fxtal, 1000000);

	/* Fvco = Fvco/10 */
	Fvco = (state->TG_LO/10000) * divider_val * Fref_TG;

	tg_lo = (((Fmax/10 - Fvco)/100)*32) / ((Fmax-Fmin)/1000)+8;

	/* below equation is same as above but much harder to debug.
	 *
	 * static u32 MXL_GetXtalInt(u32 Xtal_Freq)
	 * {
	 *	if ((Xtal_Freq % 1000000) == 0)
	 *		return (Xtal_Freq / 10000);
	 *	else
	 *		return (((Xtal_Freq / 1000000) + 1)*100);
	 * }
	 *
	 * u32 Xtal_Int = MXL_GetXtalInt(state->Fxtal);
	 * tg_lo = ( ((Fmax/10000 * Xtal_Int)/100) -
	 * ((state->TG_LO/10000)*divider_val *
	 * (state->Fxtal/10000)/100) )*32/((Fmax-Fmin)/10000 *
	 * Xtal_Int/100) + 8;
	 */

	status += MXL_ControlWrite(fe, TG_VCO_BIAS , tg_lo);

	/* add for 2.6.5 Special setting for QAM */
	if (state->Mod_Type == MXL_QAM) {
		if (state->config->qam_gain != 0)
			status += MXL_ControlWrite(fe, RFSYN_CHP_GAIN,
						   state->config->qam_gain);
		else if (state->RF_IN < 680000000)
			status += MXL_ControlWrite(fe, RFSYN_CHP_GAIN, 3);
		else
			status += MXL_ControlWrite(fe, RFSYN_CHP_GAIN, 2);
	}

	/* Off Chip Tracking Filter Control */
	if (state->TF_Type == MXL_TF_OFF) {
		/* Tracking Filter Off State; turn off all the banks */
		status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
		status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
		status += MXL_SetGPIO(fe, 3, 1); /* Bank1 Off */
		status += MXL_SetGPIO(fe, 1, 1); /* Bank2 Off */
		status += MXL_SetGPIO(fe, 4, 1); /* Bank3 Off */
	}

	if (state->TF_Type == MXL_TF_C) /* Tracking Filter type C */ {
		status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
		status += MXL_ControlWrite(fe, DAC_DIN_A, 0);

		if (state->RF_IN >= 43000000 && state->RF_IN < 150000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
			status += MXL_ControlWrite(fe, DAC_DIN_B, 0);
			status += MXL_SetGPIO(fe, 3, 0);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 4, 1);
		}
		if (state->RF_IN >= 150000000 && state->RF_IN < 280000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
			status += MXL_ControlWrite(fe, DAC_DIN_B, 0);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 4, 1);
		}
		if (state->RF_IN >= 280000000 && state->RF_IN < 360000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
			status += MXL_ControlWrite(fe, DAC_DIN_B, 0);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 4, 0);
		}
		if (state->RF_IN >= 360000000 && state->RF_IN < 560000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
			status += MXL_ControlWrite(fe, DAC_DIN_B, 0);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 4, 0);
		}
		if (state->RF_IN >= 560000000 && state->RF_IN < 580000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
			status += MXL_ControlWrite(fe, DAC_DIN_B, 29);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 4, 0);
		}
		if (state->RF_IN >= 580000000 && state->RF_IN < 630000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
			status += MXL_ControlWrite(fe, DAC_DIN_B, 0);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 4, 0);
		}
		if (state->RF_IN >= 630000000 && state->RF_IN < 700000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
			status += MXL_ControlWrite(fe, DAC_DIN_B, 16);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 4, 1);
		}
		if (state->RF_IN >= 700000000 && state->RF_IN < 760000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
			status += MXL_ControlWrite(fe, DAC_DIN_B, 7);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 4, 1);
		}
		if (state->RF_IN >= 760000000 && state->RF_IN <= 900000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
			status += MXL_ControlWrite(fe, DAC_DIN_B, 0);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 4, 1);
		}
	}

	if (state->TF_Type == MXL_TF_C_H) {

		/* Tracking Filter type C-H for Hauppauge only */
		status += MXL_ControlWrite(fe, DAC_DIN_A, 0);

		if (state->RF_IN >= 43000000 && state->RF_IN < 150000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 1);
		}
		if (state->RF_IN >= 150000000 && state->RF_IN < 280000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 3, 0);
			status += MXL_SetGPIO(fe, 1, 1);
		}
		if (state->RF_IN >= 280000000 && state->RF_IN < 360000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 3, 0);
			status += MXL_SetGPIO(fe, 1, 0);
		}
		if (state->RF_IN >= 360000000 && state->RF_IN < 560000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 0);
		}
		if (state->RF_IN >= 560000000 && state->RF_IN < 580000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 0);
		}
		if (state->RF_IN >= 580000000 && state->RF_IN < 630000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 0);
		}
		if (state->RF_IN >= 630000000 && state->RF_IN < 700000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 1);
		}
		if (state->RF_IN >= 700000000 && state->RF_IN < 760000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 1);
		}
		if (state->RF_IN >= 760000000 && state->RF_IN <= 900000000) {
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 1);
		}
	}

	if (state->TF_Type == MXL_TF_D) { /* Tracking Filter type D */

		status += MXL_ControlWrite(fe, DAC_DIN_B, 0);

		if (state->RF_IN >= 43000000 && state->RF_IN < 174000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 174000000 && state->RF_IN < 250000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 250000000 && state->RF_IN < 310000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 310000000 && state->RF_IN < 360000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 360000000 && state->RF_IN < 470000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 470000000 && state->RF_IN < 640000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 640000000 && state->RF_IN <= 900000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 1);
		}
	}

	if (state->TF_Type == MXL_TF_D_L) {

		/* Tracking Filter type D-L for Lumanate ONLY change 2.6.3 */
		status += MXL_ControlWrite(fe, DAC_DIN_A, 0);

		/* if UHF and terrestrial => Turn off Tracking Filter */
		if (state->RF_IN >= 471000000 &&
			(state->RF_IN - 471000000)%6000000 != 0) {
			/* Turn off all the banks */
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
			status += MXL_ControlWrite(fe, AGC_IF, 10);
		} else {
			/* if VHF or cable => Turn on Tracking Filter */
			if (state->RF_IN >= 43000000 &&
				state->RF_IN < 140000000) {

				status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
				status += MXL_SetGPIO(fe, 4, 1);
				status += MXL_SetGPIO(fe, 1, 1);
				status += MXL_SetGPIO(fe, 3, 0);
			}
			if (state->RF_IN >= 140000000 &&
				state->RF_IN < 240000000) {
				status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
				status += MXL_SetGPIO(fe, 4, 1);
				status += MXL_SetGPIO(fe, 1, 0);
				status += MXL_SetGPIO(fe, 3, 0);
			}
			if (state->RF_IN >= 240000000 &&
				state->RF_IN < 340000000) {
				status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
				status += MXL_SetGPIO(fe, 4, 0);
				status += MXL_SetGPIO(fe, 1, 1);
				status += MXL_SetGPIO(fe, 3, 0);
			}
			if (state->RF_IN >= 340000000 &&
				state->RF_IN < 430000000) {
				status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
				status += MXL_SetGPIO(fe, 4, 0);
				status += MXL_SetGPIO(fe, 1, 0);
				status += MXL_SetGPIO(fe, 3, 1);
			}
			if (state->RF_IN >= 430000000 &&
				state->RF_IN < 470000000) {
				status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
				status += MXL_SetGPIO(fe, 4, 1);
				status += MXL_SetGPIO(fe, 1, 0);
				status += MXL_SetGPIO(fe, 3, 1);
			}
			if (state->RF_IN >= 470000000 &&
				state->RF_IN < 570000000) {
				status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
				status += MXL_SetGPIO(fe, 4, 0);
				status += MXL_SetGPIO(fe, 1, 0);
				status += MXL_SetGPIO(fe, 3, 1);
			}
			if (state->RF_IN >= 570000000 &&
				state->RF_IN < 620000000) {
				status += MXL_ControlWrite(fe, DAC_A_ENABLE, 0);
				status += MXL_SetGPIO(fe, 4, 0);
				status += MXL_SetGPIO(fe, 1, 1);
				status += MXL_SetGPIO(fe, 3, 1);
			}
			if (state->RF_IN >= 620000000 &&
				state->RF_IN < 760000000) {
				status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
				status += MXL_SetGPIO(fe, 4, 0);
				status += MXL_SetGPIO(fe, 1, 1);
				status += MXL_SetGPIO(fe, 3, 1);
			}
			if (state->RF_IN >= 760000000 &&
				state->RF_IN <= 900000000) {
				status += MXL_ControlWrite(fe, DAC_A_ENABLE, 1);
				status += MXL_SetGPIO(fe, 4, 1);
				status += MXL_SetGPIO(fe, 1, 1);
				status += MXL_SetGPIO(fe, 3, 1);
			}
		}
	}

	if (state->TF_Type == MXL_TF_E) /* Tracking Filter type E */ {

		status += MXL_ControlWrite(fe, DAC_DIN_B, 0);

		if (state->RF_IN >= 43000000 && state->RF_IN < 174000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 174000000 && state->RF_IN < 250000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 250000000 && state->RF_IN < 310000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 310000000 && state->RF_IN < 360000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 360000000 && state->RF_IN < 470000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 470000000 && state->RF_IN < 640000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 640000000 && state->RF_IN <= 900000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 1);
		}
	}

	if (state->TF_Type == MXL_TF_F) {

		/* Tracking Filter type F */
		status += MXL_ControlWrite(fe, DAC_DIN_B, 0);

		if (state->RF_IN >= 43000000 && state->RF_IN < 160000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 160000000 && state->RF_IN < 210000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 210000000 && state->RF_IN < 300000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 300000000 && state->RF_IN < 390000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 390000000 && state->RF_IN < 515000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 515000000 && state->RF_IN < 650000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 650000000 && state->RF_IN <= 900000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 1);
		}
	}

	if (state->TF_Type == MXL_TF_E_2) {

		/* Tracking Filter type E_2 */
		status += MXL_ControlWrite(fe, DAC_DIN_B, 0);

		if (state->RF_IN >= 43000000 && state->RF_IN < 174000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 174000000 && state->RF_IN < 250000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 250000000 && state->RF_IN < 350000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 350000000 && state->RF_IN < 400000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 400000000 && state->RF_IN < 570000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 570000000 && state->RF_IN < 770000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 770000000 && state->RF_IN <= 900000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 1);
		}
	}

	if (state->TF_Type == MXL_TF_G) {

		/* Tracking Filter type G add for v2.6.8 */
		status += MXL_ControlWrite(fe, DAC_DIN_B, 0);

		if (state->RF_IN >= 50000000 && state->RF_IN < 190000000) {

			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 190000000 && state->RF_IN < 280000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 280000000 && state->RF_IN < 350000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 350000000 && state->RF_IN < 400000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 400000000 && state->RF_IN < 470000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 470000000 && state->RF_IN < 640000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 640000000 && state->RF_IN < 820000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 820000000 && state->RF_IN <= 900000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 1);
		}
	}

	if (state->TF_Type == MXL_TF_E_NA) {

		/* Tracking Filter type E-NA for Empia ONLY change for 2.6.8 */
		status += MXL_ControlWrite(fe, DAC_DIN_B, 0);

		/* if UHF and terrestrial=> Turn off Tracking Filter */
		if (state->RF_IN >= 471000000 &&
			(state->RF_IN - 471000000)%6000000 != 0) {

			/* Turn off all the banks */
			status += MXL_SetGPIO(fe, 3, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);

			/* 2.6.12 Turn on RSSI */
			status += MXL_ControlWrite(fe, SEQ_EXTSYNTHCALIF, 1);
			status += MXL_ControlWrite(fe, SEQ_EXTDCCAL, 1);
			status += MXL_ControlWrite(fe, AGC_EN_RSSI, 1);
			status += MXL_ControlWrite(fe, RFA_ENCLKRFAGC, 1);

			/* RSSI reference point */
			status += MXL_ControlWrite(fe, RFA_RSSI_REFH, 5);
			status += MXL_ControlWrite(fe, RFA_RSSI_REF, 3);
			status += MXL_ControlWrite(fe, RFA_RSSI_REFL, 2);

			/* following parameter is from analog OTA mode,
			 * can be change to seek better performance */
			status += MXL_ControlWrite(fe, RFSYN_CHP_GAIN, 3);
		} else {
		/* if VHF or Cable =>  Turn on Tracking Filter */

		/* 2.6.12 Turn off RSSI */
		status += MXL_ControlWrite(fe, AGC_EN_RSSI, 0);

		/* change back from above condition */
		status += MXL_ControlWrite(fe, RFSYN_CHP_GAIN, 5);


		if (state->RF_IN >= 43000000 && state->RF_IN < 174000000) {

			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 174000000 && state->RF_IN < 250000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 0);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 250000000 && state->RF_IN < 350000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		if (state->RF_IN >= 350000000 && state->RF_IN < 400000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 0);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 400000000 && state->RF_IN < 570000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 0);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 570000000 && state->RF_IN < 770000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 0);
		}
		if (state->RF_IN >= 770000000 && state->RF_IN <= 900000000) {
			status += MXL_ControlWrite(fe, DAC_B_ENABLE, 1);
			status += MXL_SetGPIO(fe, 4, 1);
			status += MXL_SetGPIO(fe, 1, 1);
			status += MXL_SetGPIO(fe, 3, 1);
		}
		}
	}
	return status ;
}