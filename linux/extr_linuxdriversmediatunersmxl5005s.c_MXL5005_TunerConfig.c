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
typedef  void* u8 ;
typedef  void* u32 ;
typedef  void* u16 ;
struct mxl5005s_state {void* TF_Type; void* Mod_Type; void* EN_RSSI; void* CAPSELECT; void* DIV_OUT; void* CLOCK_OUT; void* IF_OUT_LOAD; void* TOP; void* AGC_Mode; void* Fxtal; void* IF_OUT; void* Chan_Bandwidth; void* IF_Mode; void* Mode; } ;
struct dvb_frontend {struct mxl5005s_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  InitTunerControls (struct dvb_frontend*) ; 
 int /*<<< orphan*/  MXL_SynthIFLO_Calc (struct dvb_frontend*) ; 

__attribute__((used)) static u16 MXL5005_TunerConfig(struct dvb_frontend *fe,
	u8	Mode,		/* 0: Analog Mode ; 1: Digital Mode */
	u8	IF_mode,	/* for Analog Mode, 0: zero IF; 1: low IF */
	u32	Bandwidth,	/* filter  channel bandwidth (6, 7, 8) */
	u32	IF_out,		/* Desired IF Out Frequency */
	u32	Fxtal,		/* XTAL Frequency */
	u8	AGC_Mode,	/* AGC Mode - Dual AGC: 0, Single AGC: 1 */
	u16	TOP,		/* 0: Dual AGC; Value: take over point */
	u16	IF_OUT_LOAD,	/* IF Out Load Resistor (200 / 300 Ohms) */
	u8	CLOCK_OUT,	/* 0: turn off clk out; 1: turn on clock out */
	u8	DIV_OUT,	/* 0: Div-1; 1: Div-4 */
	u8	CAPSELECT,	/* 0: disable On-Chip pulling cap; 1: enable */
	u8	EN_RSSI,	/* 0: disable RSSI; 1: enable RSSI */

	/* Modulation Type; */
	/* 0 - Default;	1 - DVB-T; 2 - ATSC; 3 - QAM; 4 - Analog Cable */
	u8	Mod_Type,

	/* Tracking Filter */
	/* 0 - Default; 1 - Off; 2 - Type C; 3 - Type C-H */
	u8	TF_Type
	)
{
	struct mxl5005s_state *state = fe->tuner_priv;

	state->Mode = Mode;
	state->IF_Mode = IF_mode;
	state->Chan_Bandwidth = Bandwidth;
	state->IF_OUT = IF_out;
	state->Fxtal = Fxtal;
	state->AGC_Mode = AGC_Mode;
	state->TOP = TOP;
	state->IF_OUT_LOAD = IF_OUT_LOAD;
	state->CLOCK_OUT = CLOCK_OUT;
	state->DIV_OUT = DIV_OUT;
	state->CAPSELECT = CAPSELECT;
	state->EN_RSSI = EN_RSSI;
	state->Mod_Type = Mod_Type;
	state->TF_Type = TF_Type;

	/* Initialize all the controls and registers */
	InitTunerControls(fe);

	/* Synthesizer LO frequency calculation */
	MXL_SynthIFLO_Calc(fe);

	return 0;
}