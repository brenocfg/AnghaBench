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
typedef  int /*<<< orphan*/  u16 ;
struct mxl5005s_state {scalar_t__ Mode; int Chan_Bandwidth; int IF_Mode; int AGC_Mode; int TOP; int IF_OUT_LOAD; unsigned long IF_OUT; int DIV_OUT; unsigned long Fxtal; scalar_t__ EN_RSSI; scalar_t__ Mod_Type; scalar_t__ CAPSELECT; scalar_t__ CLOCK_OUT; } ;
struct dvb_frontend {struct mxl5005s_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC_EN_RSSI ; 
 int /*<<< orphan*/  AGC_IF ; 
 int /*<<< orphan*/  AGC_RF ; 
 int /*<<< orphan*/  BB_ALPF_BANDSELECT ; 
 int /*<<< orphan*/  BB_BUF ; 
 int /*<<< orphan*/  BB_BUF_OA ; 
 int /*<<< orphan*/  BB_DLPF_BANDSEL ; 
 int /*<<< orphan*/  BB_INITSTATE_DLPF_TUNE ; 
 int /*<<< orphan*/  BB_IQSWAP ; 
 int /*<<< orphan*/  BB_MODE ; 
 int /*<<< orphan*/  DN_IQTN_AMP_CUT ; 
 int /*<<< orphan*/  DRV_RES_SEL ; 
 int /*<<< orphan*/  EN_3P ; 
 int /*<<< orphan*/  EN_AAF ; 
 int /*<<< orphan*/  EN_AUX_3P ; 
 int /*<<< orphan*/  EN_CHP_LIN_B ; 
 int /*<<< orphan*/  IF_SEL_DBL ; 
 int /*<<< orphan*/  I_DRIVER ; 
 scalar_t__ MXL_ANALOG_CABLE ; 
 scalar_t__ MXL_ANALOG_OTA ; 
 scalar_t__ MXL_ATSC ; 
 int MXL_Ceiling (unsigned long,int) ; 
 scalar_t__ MXL_ControlWrite (struct dvb_frontend*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MXL_DIGITAL_MODE ; 
 scalar_t__ MXL_DVBT ; 
 scalar_t__ MXL_IFSynthInit (struct dvb_frontend*) ; 
 scalar_t__ MXL_OverwriteICDefault (struct dvb_frontend*) ; 
 scalar_t__ MXL_QAM ; 
 int /*<<< orphan*/  RFA_CEIL ; 
 int /*<<< orphan*/  RFA_ENCLKRFAGC ; 
 int /*<<< orphan*/  RFA_FLR ; 
 int /*<<< orphan*/  RFA_RSSI_REF ; 
 int /*<<< orphan*/  RFA_RSSI_REFH ; 
 int /*<<< orphan*/  RFA_RSSI_REFL ; 
 int /*<<< orphan*/  RFSYN_CHP_GAIN ; 
 int /*<<< orphan*/  RFSYN_EN_CHP_HIGAIN ; 
 int /*<<< orphan*/  RFSYN_R_DIV ; 
 int /*<<< orphan*/  SEL_AAF_BAND ; 
 int /*<<< orphan*/  SEQ_ENCLK16_CLK_OUT ; 
 int /*<<< orphan*/  SEQ_EXTDCCAL ; 
 int /*<<< orphan*/  SEQ_EXTIQFSMPULSE ; 
 int /*<<< orphan*/  SEQ_EXTSYNTHCALIF ; 
 int /*<<< orphan*/  SEQ_SEL4_16B ; 
 int /*<<< orphan*/  TG_R_DIV ; 
 int /*<<< orphan*/  XTAL_CAPSELECT ; 

__attribute__((used)) static u16 MXL_BlockInit(struct dvb_frontend *fe)
{
	struct mxl5005s_state *state = fe->tuner_priv;
	u16 status = 0;

	status += MXL_OverwriteICDefault(fe);

	/* Downconverter Control Dig Ana */
	status += MXL_ControlWrite(fe, DN_IQTN_AMP_CUT, state->Mode ? 1 : 0);

	/* Filter Control  Dig  Ana */
	status += MXL_ControlWrite(fe, BB_MODE, state->Mode ? 0 : 1);
	status += MXL_ControlWrite(fe, BB_BUF, state->Mode ? 3 : 2);
	status += MXL_ControlWrite(fe, BB_BUF_OA, state->Mode ? 1 : 0);
	status += MXL_ControlWrite(fe, BB_IQSWAP, state->Mode ? 0 : 1);
	status += MXL_ControlWrite(fe, BB_INITSTATE_DLPF_TUNE, 0);

	/* Initialize Low-Pass Filter */
	if (state->Mode) { /* Digital Mode */
		switch (state->Chan_Bandwidth) {
		case 8000000:
			status += MXL_ControlWrite(fe, BB_DLPF_BANDSEL, 0);
			break;
		case 7000000:
			status += MXL_ControlWrite(fe, BB_DLPF_BANDSEL, 2);
			break;
		case 6000000:
			status += MXL_ControlWrite(fe,
					BB_DLPF_BANDSEL, 3);
			break;
		}
	} else { /* Analog Mode */
		switch (state->Chan_Bandwidth) {
		case 8000000:	/* Low Zero */
			status += MXL_ControlWrite(fe, BB_ALPF_BANDSELECT,
					(state->IF_Mode ? 0 : 3));
			break;
		case 7000000:
			status += MXL_ControlWrite(fe, BB_ALPF_BANDSELECT,
					(state->IF_Mode ? 1 : 4));
			break;
		case 6000000:
			status += MXL_ControlWrite(fe, BB_ALPF_BANDSELECT,
					(state->IF_Mode ? 2 : 5));
			break;
		}
	}

	/* Charge Pump Control Dig  Ana */
	status += MXL_ControlWrite(fe, RFSYN_CHP_GAIN, state->Mode ? 5 : 8);
	status += MXL_ControlWrite(fe,
		RFSYN_EN_CHP_HIGAIN, state->Mode ? 1 : 1);
	status += MXL_ControlWrite(fe, EN_CHP_LIN_B, state->Mode ? 0 : 0);

	/* AGC TOP Control */
	if (state->AGC_Mode == 0) /* Dual AGC */ {
		status += MXL_ControlWrite(fe, AGC_IF, 15);
		status += MXL_ControlWrite(fe, AGC_RF, 15);
	} else /*  Single AGC Mode Dig  Ana */
		status += MXL_ControlWrite(fe, AGC_RF, state->Mode ? 15 : 12);

	if (state->TOP == 55) /* TOP == 5.5 */
		status += MXL_ControlWrite(fe, AGC_IF, 0x0);

	if (state->TOP == 72) /* TOP == 7.2 */
		status += MXL_ControlWrite(fe, AGC_IF, 0x1);

	if (state->TOP == 92) /* TOP == 9.2 */
		status += MXL_ControlWrite(fe, AGC_IF, 0x2);

	if (state->TOP == 110) /* TOP == 11.0 */
		status += MXL_ControlWrite(fe, AGC_IF, 0x3);

	if (state->TOP == 129) /* TOP == 12.9 */
		status += MXL_ControlWrite(fe, AGC_IF, 0x4);

	if (state->TOP == 147) /* TOP == 14.7 */
		status += MXL_ControlWrite(fe, AGC_IF, 0x5);

	if (state->TOP == 168) /* TOP == 16.8 */
		status += MXL_ControlWrite(fe, AGC_IF, 0x6);

	if (state->TOP == 194) /* TOP == 19.4 */
		status += MXL_ControlWrite(fe, AGC_IF, 0x7);

	if (state->TOP == 212) /* TOP == 21.2 */
		status += MXL_ControlWrite(fe, AGC_IF, 0x9);

	if (state->TOP == 232) /* TOP == 23.2 */
		status += MXL_ControlWrite(fe, AGC_IF, 0xA);

	if (state->TOP == 252) /* TOP == 25.2 */
		status += MXL_ControlWrite(fe, AGC_IF, 0xB);

	if (state->TOP == 271) /* TOP == 27.1 */
		status += MXL_ControlWrite(fe, AGC_IF, 0xC);

	if (state->TOP == 292) /* TOP == 29.2 */
		status += MXL_ControlWrite(fe, AGC_IF, 0xD);

	if (state->TOP == 317) /* TOP == 31.7 */
		status += MXL_ControlWrite(fe, AGC_IF, 0xE);

	if (state->TOP == 349) /* TOP == 34.9 */
		status += MXL_ControlWrite(fe, AGC_IF, 0xF);

	/* IF Synthesizer Control */
	status += MXL_IFSynthInit(fe);

	/* IF UpConverter Control */
	if (state->IF_OUT_LOAD == 200) {
		status += MXL_ControlWrite(fe, DRV_RES_SEL, 6);
		status += MXL_ControlWrite(fe, I_DRIVER, 2);
	}
	if (state->IF_OUT_LOAD == 300) {
		status += MXL_ControlWrite(fe, DRV_RES_SEL, 4);
		status += MXL_ControlWrite(fe, I_DRIVER, 1);
	}

	/* Anti-Alias Filtering Control
	 * initialise Anti-Aliasing Filter
	 */
	if (state->Mode) { /* Digital Mode */
		if (state->IF_OUT >= 4000000UL && state->IF_OUT <= 6280000UL) {
			status += MXL_ControlWrite(fe, EN_AAF, 1);
			status += MXL_ControlWrite(fe, EN_3P, 1);
			status += MXL_ControlWrite(fe, EN_AUX_3P, 1);
			status += MXL_ControlWrite(fe, SEL_AAF_BAND, 0);
		}
		if ((state->IF_OUT == 36125000UL) ||
			(state->IF_OUT == 36150000UL)) {
			status += MXL_ControlWrite(fe, EN_AAF, 1);
			status += MXL_ControlWrite(fe, EN_3P, 1);
			status += MXL_ControlWrite(fe, EN_AUX_3P, 1);
			status += MXL_ControlWrite(fe, SEL_AAF_BAND, 1);
		}
		if (state->IF_OUT > 36150000UL) {
			status += MXL_ControlWrite(fe, EN_AAF, 0);
			status += MXL_ControlWrite(fe, EN_3P, 1);
			status += MXL_ControlWrite(fe, EN_AUX_3P, 1);
			status += MXL_ControlWrite(fe, SEL_AAF_BAND, 1);
		}
	} else { /* Analog Mode */
		if (state->IF_OUT >= 4000000UL && state->IF_OUT <= 5000000UL) {
			status += MXL_ControlWrite(fe, EN_AAF, 1);
			status += MXL_ControlWrite(fe, EN_3P, 1);
			status += MXL_ControlWrite(fe, EN_AUX_3P, 1);
			status += MXL_ControlWrite(fe, SEL_AAF_BAND, 0);
		}
		if (state->IF_OUT > 5000000UL) {
			status += MXL_ControlWrite(fe, EN_AAF, 0);
			status += MXL_ControlWrite(fe, EN_3P, 0);
			status += MXL_ControlWrite(fe, EN_AUX_3P, 0);
			status += MXL_ControlWrite(fe, SEL_AAF_BAND, 0);
		}
	}

	/* Demod Clock Out */
	if (state->CLOCK_OUT)
		status += MXL_ControlWrite(fe, SEQ_ENCLK16_CLK_OUT, 1);
	else
		status += MXL_ControlWrite(fe, SEQ_ENCLK16_CLK_OUT, 0);

	if (state->DIV_OUT == 1)
		status += MXL_ControlWrite(fe, SEQ_SEL4_16B, 1);
	if (state->DIV_OUT == 0)
		status += MXL_ControlWrite(fe, SEQ_SEL4_16B, 0);

	/* Crystal Control */
	if (state->CAPSELECT)
		status += MXL_ControlWrite(fe, XTAL_CAPSELECT, 1);
	else
		status += MXL_ControlWrite(fe, XTAL_CAPSELECT, 0);

	if (state->Fxtal >= 12000000UL && state->Fxtal <= 16000000UL)
		status += MXL_ControlWrite(fe, IF_SEL_DBL, 1);
	if (state->Fxtal > 16000000UL && state->Fxtal <= 32000000UL)
		status += MXL_ControlWrite(fe, IF_SEL_DBL, 0);

	if (state->Fxtal >= 12000000UL && state->Fxtal <= 22000000UL)
		status += MXL_ControlWrite(fe, RFSYN_R_DIV, 3);
	if (state->Fxtal > 22000000UL && state->Fxtal <= 32000000UL)
		status += MXL_ControlWrite(fe, RFSYN_R_DIV, 0);

	/* Misc Controls */
	if (state->Mode == 0 && state->IF_Mode == 1) /* Analog LowIF mode */
		status += MXL_ControlWrite(fe, SEQ_EXTIQFSMPULSE, 0);
	else
		status += MXL_ControlWrite(fe, SEQ_EXTIQFSMPULSE, 1);

	/* status += MXL_ControlRead(fe, IF_DIVVAL, &IF_DIVVAL_Val); */

	/* Set TG_R_DIV */
	status += MXL_ControlWrite(fe, TG_R_DIV,
		MXL_Ceiling(state->Fxtal, 1000000));

	/* Apply Default value to BB_INITSTATE_DLPF_TUNE */

	/* RSSI Control */
	if (state->EN_RSSI) {
		status += MXL_ControlWrite(fe, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(fe, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(fe, AGC_EN_RSSI, 1);
		status += MXL_ControlWrite(fe, RFA_ENCLKRFAGC, 1);

		/* RSSI reference point */
		status += MXL_ControlWrite(fe, RFA_RSSI_REF, 2);
		status += MXL_ControlWrite(fe, RFA_RSSI_REFH, 3);
		status += MXL_ControlWrite(fe, RFA_RSSI_REFL, 1);

		/* TOP point */
		status += MXL_ControlWrite(fe, RFA_FLR, 0);
		status += MXL_ControlWrite(fe, RFA_CEIL, 12);
	}

	/* Modulation type bit settings
	 * Override the control values preset
	 */
	if (state->Mod_Type == MXL_DVBT) /* DVB-T Mode */ {
		state->AGC_Mode = 1; /* Single AGC Mode */

		/* Enable RSSI */
		status += MXL_ControlWrite(fe, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(fe, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(fe, AGC_EN_RSSI, 1);
		status += MXL_ControlWrite(fe, RFA_ENCLKRFAGC, 1);

		/* RSSI reference point */
		status += MXL_ControlWrite(fe, RFA_RSSI_REF, 3);
		status += MXL_ControlWrite(fe, RFA_RSSI_REFH, 5);
		status += MXL_ControlWrite(fe, RFA_RSSI_REFL, 1);

		/* TOP point */
		status += MXL_ControlWrite(fe, RFA_FLR, 2);
		status += MXL_ControlWrite(fe, RFA_CEIL, 13);
		if (state->IF_OUT <= 6280000UL)	/* Low IF */
			status += MXL_ControlWrite(fe, BB_IQSWAP, 0);
		else /* High IF */
			status += MXL_ControlWrite(fe, BB_IQSWAP, 1);

	}
	if (state->Mod_Type == MXL_ATSC) /* ATSC Mode */ {
		state->AGC_Mode = 1;	/* Single AGC Mode */

		/* Enable RSSI */
		status += MXL_ControlWrite(fe, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(fe, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(fe, AGC_EN_RSSI, 1);
		status += MXL_ControlWrite(fe, RFA_ENCLKRFAGC, 1);

		/* RSSI reference point */
		status += MXL_ControlWrite(fe, RFA_RSSI_REF, 2);
		status += MXL_ControlWrite(fe, RFA_RSSI_REFH, 4);
		status += MXL_ControlWrite(fe, RFA_RSSI_REFL, 1);

		/* TOP point */
		status += MXL_ControlWrite(fe, RFA_FLR, 2);
		status += MXL_ControlWrite(fe, RFA_CEIL, 13);
		status += MXL_ControlWrite(fe, BB_INITSTATE_DLPF_TUNE, 1);
		/* Low Zero */
		status += MXL_ControlWrite(fe, RFSYN_CHP_GAIN, 5);

		if (state->IF_OUT <= 6280000UL)	/* Low IF */
			status += MXL_ControlWrite(fe, BB_IQSWAP, 0);
		else /* High IF */
			status += MXL_ControlWrite(fe, BB_IQSWAP, 1);
	}
	if (state->Mod_Type == MXL_QAM) /* QAM Mode */ {
		state->Mode = MXL_DIGITAL_MODE;

		/* state->AGC_Mode = 1; */ /* Single AGC Mode */

		/* Disable RSSI */	/* change here for v2.6.5 */
		status += MXL_ControlWrite(fe, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(fe, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(fe, AGC_EN_RSSI, 0);
		status += MXL_ControlWrite(fe, RFA_ENCLKRFAGC, 1);

		/* RSSI reference point */
		status += MXL_ControlWrite(fe, RFA_RSSI_REFH, 5);
		status += MXL_ControlWrite(fe, RFA_RSSI_REF, 3);
		status += MXL_ControlWrite(fe, RFA_RSSI_REFL, 2);
		/* change here for v2.6.5 */
		status += MXL_ControlWrite(fe, RFSYN_CHP_GAIN, 3);

		if (state->IF_OUT <= 6280000UL)	/* Low IF */
			status += MXL_ControlWrite(fe, BB_IQSWAP, 0);
		else /* High IF */
			status += MXL_ControlWrite(fe, BB_IQSWAP, 1);
		status += MXL_ControlWrite(fe, RFSYN_CHP_GAIN, 2);

	}
	if (state->Mod_Type == MXL_ANALOG_CABLE) {
		/* Analog Cable Mode */
		/* state->Mode = MXL_DIGITAL_MODE; */

		state->AGC_Mode = 1; /* Single AGC Mode */

		/* Disable RSSI */
		status += MXL_ControlWrite(fe, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(fe, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(fe, AGC_EN_RSSI, 0);
		status += MXL_ControlWrite(fe, RFA_ENCLKRFAGC, 1);
		/* change for 2.6.3 */
		status += MXL_ControlWrite(fe, AGC_IF, 1);
		status += MXL_ControlWrite(fe, AGC_RF, 15);
		status += MXL_ControlWrite(fe, BB_IQSWAP, 1);
	}

	if (state->Mod_Type == MXL_ANALOG_OTA) {
		/* Analog OTA Terrestrial mode add for 2.6.7 */
		/* state->Mode = MXL_ANALOG_MODE; */

		/* Enable RSSI */
		status += MXL_ControlWrite(fe, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(fe, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(fe, AGC_EN_RSSI, 1);
		status += MXL_ControlWrite(fe, RFA_ENCLKRFAGC, 1);

		/* RSSI reference point */
		status += MXL_ControlWrite(fe, RFA_RSSI_REFH, 5);
		status += MXL_ControlWrite(fe, RFA_RSSI_REF, 3);
		status += MXL_ControlWrite(fe, RFA_RSSI_REFL, 2);
		status += MXL_ControlWrite(fe, RFSYN_CHP_GAIN, 3);
		status += MXL_ControlWrite(fe, BB_IQSWAP, 1);
	}

	/* RSSI disable */
	if (state->EN_RSSI == 0) {
		status += MXL_ControlWrite(fe, SEQ_EXTSYNTHCALIF, 1);
		status += MXL_ControlWrite(fe, SEQ_EXTDCCAL, 1);
		status += MXL_ControlWrite(fe, AGC_EN_RSSI, 0);
		status += MXL_ControlWrite(fe, RFA_ENCLKRFAGC, 1);
	}

	return status;
}