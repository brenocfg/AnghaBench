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
struct stb0899_internal {int direction; long derot_percent; long mclk; long derot_step; int t_data; scalar_t__ status; int derot_freq; int fecrate; scalar_t__ freq; scalar_t__ t_derot; scalar_t__ t_agc2; scalar_t__ t_agc1; scalar_t__ sub_range; int /*<<< orphan*/  master_clk; } ;
struct stb0899_params {int srate; scalar_t__ freq; } ;
struct stb0899_state {int /*<<< orphan*/  verbose; int /*<<< orphan*/  frontend; struct stb0899_config* config; struct stb0899_internal internal; struct stb0899_params params; } ;
struct stb0899_config {int /*<<< orphan*/  (* tuner_get_bandwidth ) (int /*<<< orphan*/ *,int*) ;int /*<<< orphan*/  (* tuner_get_frequency ) (int /*<<< orphan*/ *,scalar_t__*) ;int /*<<< orphan*/  (* tuner_set_frequency ) (int /*<<< orphan*/ *,scalar_t__) ;} ;
typedef  size_t s32 ;
typedef  enum stb0899_status { ____Placeholder_stb0899_status } stb0899_status ;

/* Variables and functions */
 scalar_t__ AGC1OK ; 
 int /*<<< orphan*/  BETA ; 
 scalar_t__ CARRIEROK ; 
 int /*<<< orphan*/  CFD_ON ; 
 scalar_t__ DATAOK ; 
 int /*<<< orphan*/  DEMAPVIT_KDIVIDER ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  FRESRS ; 
 scalar_t__ NOAGC1 ; 
 scalar_t__ RANGEOK ; 
 int /*<<< orphan*/  STB0899_ACLC ; 
 int /*<<< orphan*/  STB0899_BCLC ; 
 int /*<<< orphan*/  STB0899_CFD ; 
 int /*<<< orphan*/  STB0899_CFRM ; 
 int /*<<< orphan*/  STB0899_DEMAPVIT ; 
 int /*<<< orphan*/  STB0899_EQON ; 
 int /*<<< orphan*/  STB0899_EQUAI1 ; 
#define  STB0899_FEC_1_2 133 
#define  STB0899_FEC_2_3 132 
#define  STB0899_FEC_3_4 131 
#define  STB0899_FEC_5_6 130 
#define  STB0899_FEC_6_7 129 
#define  STB0899_FEC_7_8 128 
 int STB0899_GETFIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STB0899_PLPARM ; 
 int /*<<< orphan*/  STB0899_RTC ; 
 int /*<<< orphan*/  STB0899_RTF ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  STB0899_TSTRES ; 
 int /*<<< orphan*/  STB0899_VITSYNC ; 
 scalar_t__ TIMINGOK ; 
 int /*<<< orphan*/  VITCURPUN ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  next_sub_range (struct stb0899_state*) ; 
 scalar_t__ stb0899_calc_derot_time (long) ; 
 scalar_t__ stb0899_check_range (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_check_tmg (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_first_subrange (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_i2c_gate_ctrl (int /*<<< orphan*/ *,int) ; 
 int stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_read_regs (struct stb0899_state*,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ stb0899_search_carrier (struct stb0899_state*) ; 
 scalar_t__ stb0899_search_data (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_search_tmg (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_set_srate (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stb0899_write_regs (struct stb0899_state*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int*) ; 

enum stb0899_status stb0899_dvbs_algo(struct stb0899_state *state)
{
	struct stb0899_params *params		= &state->params;
	struct stb0899_internal *internal	= &state->internal;
	struct stb0899_config *config		= state->config;

	u8 bclc, reg;
	u8 cfr[2];
	u8 eq_const[10];
	s32 clnI = 3;
	u32 bandwidth = 0;

	/* BETA values rated @ 99MHz	*/
	s32 betaTab[5][4] = {
	       /*  5   10   20   30MBps */
		{ 37,  34,  32,  31 }, /* QPSK 1/2	*/
		{ 37,  35,  33,  31 }, /* QPSK 2/3	*/
		{ 37,  35,  33,  31 }, /* QPSK 3/4	*/
		{ 37,  36,  33,	 32 }, /* QPSK 5/6	*/
		{ 37,  36,  33,	 32 }  /* QPSK 7/8	*/
	};

	internal->direction = 1;

	stb0899_set_srate(state, internal->master_clk, params->srate);
	/* Carrier loop optimization versus symbol rate for acquisition*/
	if (params->srate <= 5000000) {
		stb0899_write_reg(state, STB0899_ACLC, 0x89);
		bclc = stb0899_read_reg(state, STB0899_BCLC);
		STB0899_SETFIELD_VAL(BETA, bclc, 0x1c);
		stb0899_write_reg(state, STB0899_BCLC, bclc);
		clnI = 0;
	} else if (params->srate <= 15000000) {
		stb0899_write_reg(state, STB0899_ACLC, 0xc9);
		bclc = stb0899_read_reg(state, STB0899_BCLC);
		STB0899_SETFIELD_VAL(BETA, bclc, 0x22);
		stb0899_write_reg(state, STB0899_BCLC, bclc);
		clnI = 1;
	} else if(params->srate <= 25000000) {
		stb0899_write_reg(state, STB0899_ACLC, 0x89);
		bclc = stb0899_read_reg(state, STB0899_BCLC);
		STB0899_SETFIELD_VAL(BETA, bclc, 0x27);
		stb0899_write_reg(state, STB0899_BCLC, bclc);
		clnI = 2;
	} else {
		stb0899_write_reg(state, STB0899_ACLC, 0xc8);
		bclc = stb0899_read_reg(state, STB0899_BCLC);
		STB0899_SETFIELD_VAL(BETA, bclc, 0x29);
		stb0899_write_reg(state, STB0899_BCLC, bclc);
		clnI = 3;
	}

	dprintk(state->verbose, FE_DEBUG, 1, "Set the timing loop to acquisition");
	/* Set the timing loop to acquisition	*/
	stb0899_write_reg(state, STB0899_RTC, 0x46);
	stb0899_write_reg(state, STB0899_CFD, 0xee);

	/* !! WARNING !!
	 * Do not read any status variables while acquisition,
	 * If any needed, read before the acquisition starts
	 * querying status while acquiring causes the
	 * acquisition to go bad and hence no locks.
	 */
	dprintk(state->verbose, FE_DEBUG, 1, "Derot Percent=%d Srate=%d mclk=%d",
		internal->derot_percent, params->srate, internal->mclk);

	/* Initial calculations	*/
	internal->derot_step = internal->derot_percent * (params->srate / 1000L) / internal->mclk; /* DerotStep/1000 * Fsymbol	*/
	internal->t_derot = stb0899_calc_derot_time(params->srate);
	internal->t_data = 500;

	dprintk(state->verbose, FE_DEBUG, 1, "RESET stream merger");
	/* RESET Stream merger	*/
	reg = stb0899_read_reg(state, STB0899_TSTRES);
	STB0899_SETFIELD_VAL(FRESRS, reg, 1);
	stb0899_write_reg(state, STB0899_TSTRES, reg);

	/*
	 * Set KDIVIDER to an intermediate value between
	 * 1/2 and 7/8 for acquisition
	 */
	reg = stb0899_read_reg(state, STB0899_DEMAPVIT);
	STB0899_SETFIELD_VAL(DEMAPVIT_KDIVIDER, reg, 60);
	stb0899_write_reg(state, STB0899_DEMAPVIT, reg);

	stb0899_write_reg(state, STB0899_EQON, 0x01); /* Equalizer OFF while acquiring */
	stb0899_write_reg(state, STB0899_VITSYNC, 0x19);

	stb0899_first_subrange(state);
	do {
		/* Initialisations */
		cfr[0] = cfr[1] = 0;
		stb0899_write_regs(state, STB0899_CFRM, cfr, 2); /* RESET derotator frequency	*/

		stb0899_write_reg(state, STB0899_RTF, 0);
		reg = stb0899_read_reg(state, STB0899_CFD);
		STB0899_SETFIELD_VAL(CFD_ON, reg, 1);
		stb0899_write_reg(state, STB0899_CFD, reg);

		internal->derot_freq = 0;
		internal->status = NOAGC1;

		/* enable tuner I/O */
		stb0899_i2c_gate_ctrl(&state->frontend, 1);

		/* Move tuner to frequency */
		dprintk(state->verbose, FE_DEBUG, 1, "Tuner set frequency");
		if (state->config->tuner_set_frequency)
			state->config->tuner_set_frequency(&state->frontend, internal->freq);

		if (state->config->tuner_get_frequency)
			state->config->tuner_get_frequency(&state->frontend, &internal->freq);

		msleep(internal->t_agc1 + internal->t_agc2 + internal->t_derot); /* AGC1, AGC2 and timing loop	*/
		dprintk(state->verbose, FE_DEBUG, 1, "current derot freq=%d", internal->derot_freq);
		internal->status = AGC1OK;

		/* There is signal in the band	*/
		if (config->tuner_get_bandwidth)
			config->tuner_get_bandwidth(&state->frontend, &bandwidth);

		/* disable tuner I/O */
		stb0899_i2c_gate_ctrl(&state->frontend, 0);

		if (params->srate <= bandwidth / 2)
			stb0899_search_tmg(state); /* For low rates (SCPC)	*/
		else
			stb0899_check_tmg(state); /* For high rates (MCPC)	*/

		if (internal->status == TIMINGOK) {
			dprintk(state->verbose, FE_DEBUG, 1,
				"TIMING OK ! Derot freq=%d, mclk=%d",
				internal->derot_freq, internal->mclk);

			if (stb0899_search_carrier(state) == CARRIEROK) {	/* Search for carrier	*/
				dprintk(state->verbose, FE_DEBUG, 1,
					"CARRIER OK ! Derot freq=%d, mclk=%d",
					internal->derot_freq, internal->mclk);

				if (stb0899_search_data(state) == DATAOK) {	/* Check for data	*/
					dprintk(state->verbose, FE_DEBUG, 1,
						"DATA OK ! Derot freq=%d, mclk=%d",
						internal->derot_freq, internal->mclk);

					if (stb0899_check_range(state) == RANGEOK) {
						dprintk(state->verbose, FE_DEBUG, 1,
							"RANGE OK ! derot freq=%d, mclk=%d",
							internal->derot_freq, internal->mclk);

						internal->freq = params->freq - ((internal->derot_freq * internal->mclk) / 1000);
						reg = stb0899_read_reg(state, STB0899_PLPARM);
						internal->fecrate = STB0899_GETFIELD(VITCURPUN, reg);
						dprintk(state->verbose, FE_DEBUG, 1,
							"freq=%d, internal resultant freq=%d",
							params->freq, internal->freq);

						dprintk(state->verbose, FE_DEBUG, 1,
							"internal puncture rate=%d",
							internal->fecrate);
					}
				}
			}
		}
		if (internal->status != RANGEOK)
			next_sub_range(state);

	} while (internal->sub_range && internal->status != RANGEOK);

	/* Set the timing loop to tracking	*/
	stb0899_write_reg(state, STB0899_RTC, 0x33);
	stb0899_write_reg(state, STB0899_CFD, 0xf7);
	/* if locked and range ok, set Kdiv	*/
	if (internal->status == RANGEOK) {
		dprintk(state->verbose, FE_DEBUG, 1, "Locked & Range OK !");
		stb0899_write_reg(state, STB0899_EQON, 0x41);		/* Equalizer OFF while acquiring	*/
		stb0899_write_reg(state, STB0899_VITSYNC, 0x39);	/* SN to b'11 for acquisition		*/

		/*
		 * Carrier loop optimization versus
		 * symbol Rate/Puncture Rate for Tracking
		 */
		reg = stb0899_read_reg(state, STB0899_BCLC);
		switch (internal->fecrate) {
		case STB0899_FEC_1_2:		/* 13	*/
			stb0899_write_reg(state, STB0899_DEMAPVIT, 0x1a);
			STB0899_SETFIELD_VAL(BETA, reg, betaTab[0][clnI]);
			stb0899_write_reg(state, STB0899_BCLC, reg);
			break;
		case STB0899_FEC_2_3:		/* 18	*/
			stb0899_write_reg(state, STB0899_DEMAPVIT, 44);
			STB0899_SETFIELD_VAL(BETA, reg, betaTab[1][clnI]);
			stb0899_write_reg(state, STB0899_BCLC, reg);
			break;
		case STB0899_FEC_3_4:		/* 21	*/
			stb0899_write_reg(state, STB0899_DEMAPVIT, 60);
			STB0899_SETFIELD_VAL(BETA, reg, betaTab[2][clnI]);
			stb0899_write_reg(state, STB0899_BCLC, reg);
			break;
		case STB0899_FEC_5_6:		/* 24	*/
			stb0899_write_reg(state, STB0899_DEMAPVIT, 75);
			STB0899_SETFIELD_VAL(BETA, reg, betaTab[3][clnI]);
			stb0899_write_reg(state, STB0899_BCLC, reg);
			break;
		case STB0899_FEC_6_7:		/* 25	*/
			stb0899_write_reg(state, STB0899_DEMAPVIT, 88);
			stb0899_write_reg(state, STB0899_ACLC, 0x88);
			stb0899_write_reg(state, STB0899_BCLC, 0x9a);
			break;
		case STB0899_FEC_7_8:		/* 26	*/
			stb0899_write_reg(state, STB0899_DEMAPVIT, 94);
			STB0899_SETFIELD_VAL(BETA, reg, betaTab[4][clnI]);
			stb0899_write_reg(state, STB0899_BCLC, reg);
			break;
		default:
			dprintk(state->verbose, FE_DEBUG, 1, "Unsupported Puncture Rate");
			break;
		}
		/* release stream merger RESET	*/
		reg = stb0899_read_reg(state, STB0899_TSTRES);
		STB0899_SETFIELD_VAL(FRESRS, reg, 0);
		stb0899_write_reg(state, STB0899_TSTRES, reg);

		/* disable carrier detector	*/
		reg = stb0899_read_reg(state, STB0899_CFD);
		STB0899_SETFIELD_VAL(CFD_ON, reg, 0);
		stb0899_write_reg(state, STB0899_CFD, reg);

		stb0899_read_regs(state, STB0899_EQUAI1, eq_const, 10);
	}

	return internal->status;
}