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
typedef  int u16 ;
struct dtv_frontend_properties {scalar_t__ inversion; int transmission_mode; int guard_interval; int hierarchy; int modulation; int code_rate_HP; int bandwidth_hz; } ;
struct drxd_state {scalar_t__ drxd_state; scalar_t__ cscd_state; int sys_clock_freq; scalar_t__ operation_mode; int /*<<< orphan*/  noise_cal; scalar_t__ type_A; struct dtv_frontend_properties props; int /*<<< orphan*/  rf_agc_cfg; int /*<<< orphan*/  if_agc_cfg; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ CSCD_INIT ; 
 scalar_t__ CSCD_SET ; 
 int DRXD_BANDWIDTH_6MHZ_IN_HZ ; 
 int DRXD_BANDWIDTH_7MHZ_IN_HZ ; 
 int DRXD_BANDWIDTH_8MHZ_IN_HZ ; 
 int DRXD_OSCDEV_DO_SCAN ; 
 scalar_t__ DRXD_STARTED ; 
 scalar_t__ DRXD_STOPPED ; 
#define  DRX_CHANNEL_AUTO 148 
#define  DRX_CHANNEL_HIGH 147 
#define  DRX_CHANNEL_LOW 146 
 int /*<<< orphan*/  EC_SB_REG_ALPHA__A ; 
 int EC_SB_REG_CONST_16QAM ; 
 int EC_SB_REG_CONST_64QAM ; 
 int EC_SB_REG_CONST_QPSK ; 
 int /*<<< orphan*/  EC_SB_REG_CONST__A ; 
 int EC_SB_REG_PRIOR_HI ; 
 int EC_SB_REG_PRIOR_LO ; 
 int /*<<< orphan*/  EC_SB_REG_PRIOR__A ; 
 int /*<<< orphan*/  EC_SB_REG_SCALE_BIT2__A ; 
 int /*<<< orphan*/  EC_SB_REG_SCALE_LSB__A ; 
 int /*<<< orphan*/  EC_SB_REG_SCALE_MSB__A ; 
 int EC_SB_REG_TR_MODE_2K ; 
 int EC_SB_REG_TR_MODE_8K ; 
 int /*<<< orphan*/  EC_SB_REG_TR_MODE__A ; 
 int EC_VD_REG_SET_CODERATE_C1_2 ; 
 int EC_VD_REG_SET_CODERATE_C2_3 ; 
 int EC_VD_REG_SET_CODERATE_C3_4 ; 
 int EC_VD_REG_SET_CODERATE_C5_6 ; 
 int EC_VD_REG_SET_CODERATE_C7_8 ; 
 int /*<<< orphan*/  EC_VD_REG_SET_CODERATE__A ; 
 int EINVAL ; 
 int /*<<< orphan*/  EQ_REG_IS_GAIN_EXP__A ; 
 int /*<<< orphan*/  EQ_REG_IS_GAIN_MAN__A ; 
 int /*<<< orphan*/  EQ_REG_OT_ALPHA__A ; 
 int /*<<< orphan*/  EQ_REG_OT_CONST__A ; 
 int /*<<< orphan*/  EQ_REG_SN_CEGAIN__A ; 
 int /*<<< orphan*/  EQ_REG_TD_TPS_PWR_OFS__A ; 
 int EQ_TD_TPS_PWR_QAM16_ALPHA1 ; 
 int EQ_TD_TPS_PWR_QAM16_ALPHA2 ; 
 int EQ_TD_TPS_PWR_QAM16_ALPHA4 ; 
 int EQ_TD_TPS_PWR_QAM16_ALPHAN ; 
 int EQ_TD_TPS_PWR_QAM64_ALPHA1 ; 
 int EQ_TD_TPS_PWR_QAM64_ALPHA2 ; 
 int EQ_TD_TPS_PWR_QAM64_ALPHA4 ; 
 int EQ_TD_TPS_PWR_QAM64_ALPHAN ; 
 int EQ_TD_TPS_PWR_QPSK ; 
 int EQ_TD_TPS_PWR_UNKNOWN ; 
#define  FEC_1_2 145 
#define  FEC_2_3 144 
#define  FEC_3_4 143 
#define  FEC_5_6 142 
#define  FEC_7_8 141 
 int /*<<< orphan*/  FE_AG_REG_IND_DEL__A ; 
 int /*<<< orphan*/  FE_IF_REG_INCR0__A ; 
 int FE_IF_REG_INCR0__M ; 
 int FE_IF_REG_INCR0__W ; 
 int /*<<< orphan*/  FE_IF_REG_INCR1__A ; 
 int FE_IF_REG_INCR1__M ; 
#define  GUARD_INTERVAL_1_16 140 
#define  GUARD_INTERVAL_1_32 139 
#define  GUARD_INTERVAL_1_4 138 
#define  GUARD_INTERVAL_1_8 137 
#define  HIERARCHY_1 136 
#define  HIERARCHY_2 135 
#define  HIERARCHY_4 134 
#define  HIERARCHY_AUTO 133 
 scalar_t__ INVERSION_ON ; 
 int InitCE (struct drxd_state*) ; 
 int InitCP (struct drxd_state*) ; 
 int InitEQ (struct drxd_state*) ; 
 int InitFT (struct drxd_state*) ; 
 int InitSC (struct drxd_state*) ; 
 int MulDiv32 (int,unsigned long long,int) ; 
 scalar_t__ OM_Default ; 
#define  QAM_16 132 
#define  QAM_64 131 
#define  QPSK 130 
 int Read16 (struct drxd_state*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int ResetECOD (struct drxd_state*) ; 
 int /*<<< orphan*/  SC_COMM_EXEC__A ; 
 int /*<<< orphan*/  SC_COMM_STATE__A ; 
 int SC_ProcStartCommand (struct drxd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_RA_RAM_BAND__A ; 
 int SC_RA_RAM_CONFIG_SLAVE__M ; 
 int /*<<< orphan*/  SC_RA_RAM_CONFIG__A ; 
 int SC_RA_RAM_EQ_IS_GAIN_16QAM_A2_EXP__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_16QAM_A2_MAN__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_16QAM_A4_EXP__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_16QAM_A4_MAN__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_16QAM_EXP__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_16QAM_MAN__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_64QAM_A2_EXP__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_64QAM_A2_MAN__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_64QAM_A4_EXP__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_64QAM_A4_MAN__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_64QAM_EXP__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_64QAM_MAN__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_QPSK_EXP__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_QPSK_MAN__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_EXP__PRE ; 
 int SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_MAN__PRE ; 
 int /*<<< orphan*/  SC_RA_RAM_LOCKTRACK_MIN ; 
 int SC_RA_RAM_OP_AUTO_CONST__M ; 
 int SC_RA_RAM_OP_AUTO_GUARD__M ; 
 int SC_RA_RAM_OP_AUTO_HIER__M ; 
 int SC_RA_RAM_OP_AUTO_MODE__M ; 
 int SC_RA_RAM_OP_AUTO_RATE__M ; 
 int SC_RA_RAM_OP_PARAM_CONST_QAM16 ; 
 int SC_RA_RAM_OP_PARAM_CONST_QAM64 ; 
 int SC_RA_RAM_OP_PARAM_CONST_QPSK ; 
 int SC_RA_RAM_OP_PARAM_GUARD_16 ; 
 int SC_RA_RAM_OP_PARAM_GUARD_32 ; 
 int SC_RA_RAM_OP_PARAM_GUARD_4 ; 
 int SC_RA_RAM_OP_PARAM_GUARD_8 ; 
 int SC_RA_RAM_OP_PARAM_HIER_A1 ; 
 int SC_RA_RAM_OP_PARAM_HIER_A2 ; 
 int SC_RA_RAM_OP_PARAM_HIER_A4 ; 
 int SC_RA_RAM_OP_PARAM_HIER_NO ; 
 int SC_RA_RAM_OP_PARAM_MODE_2K ; 
 int SC_RA_RAM_OP_PARAM_MODE_8K ; 
 int SC_RA_RAM_OP_PARAM_PRIO_HI ; 
 int SC_RA_RAM_OP_PARAM_PRIO_LO ; 
 int SC_RA_RAM_OP_PARAM_RATE_1_2 ; 
 int SC_RA_RAM_OP_PARAM_RATE_2_3 ; 
 int SC_RA_RAM_OP_PARAM_RATE_3_4 ; 
 int SC_RA_RAM_OP_PARAM_RATE_5_6 ; 
 int SC_RA_RAM_OP_PARAM_RATE_7_8 ; 
 int /*<<< orphan*/  SC_RA_RAM_PROC_LOCKTRACK ; 
 int /*<<< orphan*/  SC_RA_RAM_SAMPLE_RATE_COUNT__A ; 
 int /*<<< orphan*/  SC_RA_RAM_SW_EVENT_RUN_NMASK__M ; 
 int SC_SetPrefParamCommand (struct drxd_state*,int,int,int) ; 
 int SetCfgIfAgc (struct drxd_state*,int /*<<< orphan*/ *) ; 
 int SetCfgNoiseCalibration (struct drxd_state*,int /*<<< orphan*/ *) ; 
 int SetCfgRfAgc (struct drxd_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFrequencyShift (struct drxd_state*,int,int) ; 
 int StartDiversity (struct drxd_state*) ; 
 int StartOC (struct drxd_state*) ; 
#define  TRANSMISSION_MODE_2K 129 
#define  TRANSMISSION_MODE_8K 128 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int DRX_Start(struct drxd_state *state, s32 off)
{
	struct dtv_frontend_properties *p = &state->props;
	int status;

	u16 transmissionParams = 0;
	u16 operationMode = 0;
	u16 qpskTdTpsPwr = 0;
	u16 qam16TdTpsPwr = 0;
	u16 qam64TdTpsPwr = 0;
	u32 feIfIncr = 0;
	u32 bandwidth = 0;
	int mirrorFreqSpect;

	u16 qpskSnCeGain = 0;
	u16 qam16SnCeGain = 0;
	u16 qam64SnCeGain = 0;
	u16 qpskIsGainMan = 0;
	u16 qam16IsGainMan = 0;
	u16 qam64IsGainMan = 0;
	u16 qpskIsGainExp = 0;
	u16 qam16IsGainExp = 0;
	u16 qam64IsGainExp = 0;
	u16 bandwidthParam = 0;

	if (off < 0)
		off = (off - 500) / 1000;
	else
		off = (off + 500) / 1000;

	do {
		if (state->drxd_state != DRXD_STOPPED)
			return -1;
		status = ResetECOD(state);
		if (status < 0)
			break;
		if (state->type_A) {
			status = InitSC(state);
			if (status < 0)
				break;
		} else {
			status = InitFT(state);
			if (status < 0)
				break;
			status = InitCP(state);
			if (status < 0)
				break;
			status = InitCE(state);
			if (status < 0)
				break;
			status = InitEQ(state);
			if (status < 0)
				break;
			status = InitSC(state);
			if (status < 0)
				break;
		}

		/* Restore current IF & RF AGC settings */

		status = SetCfgIfAgc(state, &state->if_agc_cfg);
		if (status < 0)
			break;
		status = SetCfgRfAgc(state, &state->rf_agc_cfg);
		if (status < 0)
			break;

		mirrorFreqSpect = (state->props.inversion == INVERSION_ON);

		switch (p->transmission_mode) {
		default:	/* Not set, detect it automatically */
			operationMode |= SC_RA_RAM_OP_AUTO_MODE__M;
			/* fall through - try first guess DRX_FFTMODE_8K */
		case TRANSMISSION_MODE_8K:
			transmissionParams |= SC_RA_RAM_OP_PARAM_MODE_8K;
			if (state->type_A) {
				status = Write16(state, EC_SB_REG_TR_MODE__A, EC_SB_REG_TR_MODE_8K, 0x0000);
				if (status < 0)
					break;
				qpskSnCeGain = 99;
				qam16SnCeGain = 83;
				qam64SnCeGain = 67;
			}
			break;
		case TRANSMISSION_MODE_2K:
			transmissionParams |= SC_RA_RAM_OP_PARAM_MODE_2K;
			if (state->type_A) {
				status = Write16(state, EC_SB_REG_TR_MODE__A, EC_SB_REG_TR_MODE_2K, 0x0000);
				if (status < 0)
					break;
				qpskSnCeGain = 97;
				qam16SnCeGain = 71;
				qam64SnCeGain = 65;
			}
			break;
		}

		switch (p->guard_interval) {
		case GUARD_INTERVAL_1_4:
			transmissionParams |= SC_RA_RAM_OP_PARAM_GUARD_4;
			break;
		case GUARD_INTERVAL_1_8:
			transmissionParams |= SC_RA_RAM_OP_PARAM_GUARD_8;
			break;
		case GUARD_INTERVAL_1_16:
			transmissionParams |= SC_RA_RAM_OP_PARAM_GUARD_16;
			break;
		case GUARD_INTERVAL_1_32:
			transmissionParams |= SC_RA_RAM_OP_PARAM_GUARD_32;
			break;
		default:	/* Not set, detect it automatically */
			operationMode |= SC_RA_RAM_OP_AUTO_GUARD__M;
			/* try first guess 1/4 */
			transmissionParams |= SC_RA_RAM_OP_PARAM_GUARD_4;
			break;
		}

		switch (p->hierarchy) {
		case HIERARCHY_1:
			transmissionParams |= SC_RA_RAM_OP_PARAM_HIER_A1;
			if (state->type_A) {
				status = Write16(state, EQ_REG_OT_ALPHA__A, 0x0001, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_ALPHA__A, 0x0001, 0x0000);
				if (status < 0)
					break;

				qpskTdTpsPwr = EQ_TD_TPS_PWR_UNKNOWN;
				qam16TdTpsPwr = EQ_TD_TPS_PWR_QAM16_ALPHA1;
				qam64TdTpsPwr = EQ_TD_TPS_PWR_QAM64_ALPHA1;

				qpskIsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_MAN__PRE;
				qam16IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_MAN__PRE;
				qam64IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_MAN__PRE;

				qpskIsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_EXP__PRE;
				qam16IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_EXP__PRE;
				qam64IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_EXP__PRE;
			}
			break;

		case HIERARCHY_2:
			transmissionParams |= SC_RA_RAM_OP_PARAM_HIER_A2;
			if (state->type_A) {
				status = Write16(state, EQ_REG_OT_ALPHA__A, 0x0002, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_ALPHA__A, 0x0002, 0x0000);
				if (status < 0)
					break;

				qpskTdTpsPwr = EQ_TD_TPS_PWR_UNKNOWN;
				qam16TdTpsPwr = EQ_TD_TPS_PWR_QAM16_ALPHA2;
				qam64TdTpsPwr = EQ_TD_TPS_PWR_QAM64_ALPHA2;

				qpskIsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_MAN__PRE;
				qam16IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_A2_MAN__PRE;
				qam64IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_A2_MAN__PRE;

				qpskIsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_EXP__PRE;
				qam16IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_A2_EXP__PRE;
				qam64IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_A2_EXP__PRE;
			}
			break;
		case HIERARCHY_4:
			transmissionParams |= SC_RA_RAM_OP_PARAM_HIER_A4;
			if (state->type_A) {
				status = Write16(state, EQ_REG_OT_ALPHA__A, 0x0003, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_ALPHA__A, 0x0003, 0x0000);
				if (status < 0)
					break;

				qpskTdTpsPwr = EQ_TD_TPS_PWR_UNKNOWN;
				qam16TdTpsPwr = EQ_TD_TPS_PWR_QAM16_ALPHA4;
				qam64TdTpsPwr = EQ_TD_TPS_PWR_QAM64_ALPHA4;

				qpskIsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_MAN__PRE;
				qam16IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_A4_MAN__PRE;
				qam64IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_A4_MAN__PRE;

				qpskIsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_EXP__PRE;
				qam16IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_A4_EXP__PRE;
				qam64IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_A4_EXP__PRE;
			}
			break;
		case HIERARCHY_AUTO:
		default:
			/* Not set, detect it automatically, start with none */
			operationMode |= SC_RA_RAM_OP_AUTO_HIER__M;
			transmissionParams |= SC_RA_RAM_OP_PARAM_HIER_NO;
			if (state->type_A) {
				status = Write16(state, EQ_REG_OT_ALPHA__A, 0x0000, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_ALPHA__A, 0x0000, 0x0000);
				if (status < 0)
					break;

				qpskTdTpsPwr = EQ_TD_TPS_PWR_QPSK;
				qam16TdTpsPwr = EQ_TD_TPS_PWR_QAM16_ALPHAN;
				qam64TdTpsPwr = EQ_TD_TPS_PWR_QAM64_ALPHAN;

				qpskIsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_QPSK_MAN__PRE;
				qam16IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_MAN__PRE;
				qam64IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_MAN__PRE;

				qpskIsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_QPSK_EXP__PRE;
				qam16IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_EXP__PRE;
				qam64IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_EXP__PRE;
			}
			break;
		}
		if (status < 0)
			break;

		switch (p->modulation) {
		default:
			operationMode |= SC_RA_RAM_OP_AUTO_CONST__M;
			/* fall through - try first guess DRX_CONSTELLATION_QAM64 */
		case QAM_64:
			transmissionParams |= SC_RA_RAM_OP_PARAM_CONST_QAM64;
			if (state->type_A) {
				status = Write16(state, EQ_REG_OT_CONST__A, 0x0002, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_CONST__A, EC_SB_REG_CONST_64QAM, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_SCALE_MSB__A, 0x0020, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_SCALE_BIT2__A, 0x0008, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_SCALE_LSB__A, 0x0002, 0x0000);
				if (status < 0)
					break;

				status = Write16(state, EQ_REG_TD_TPS_PWR_OFS__A, qam64TdTpsPwr, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EQ_REG_SN_CEGAIN__A, qam64SnCeGain, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EQ_REG_IS_GAIN_MAN__A, qam64IsGainMan, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EQ_REG_IS_GAIN_EXP__A, qam64IsGainExp, 0x0000);
				if (status < 0)
					break;
			}
			break;
		case QPSK:
			transmissionParams |= SC_RA_RAM_OP_PARAM_CONST_QPSK;
			if (state->type_A) {
				status = Write16(state, EQ_REG_OT_CONST__A, 0x0000, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_CONST__A, EC_SB_REG_CONST_QPSK, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_SCALE_MSB__A, 0x0010, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_SCALE_BIT2__A, 0x0000, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_SCALE_LSB__A, 0x0000, 0x0000);
				if (status < 0)
					break;

				status = Write16(state, EQ_REG_TD_TPS_PWR_OFS__A, qpskTdTpsPwr, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EQ_REG_SN_CEGAIN__A, qpskSnCeGain, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EQ_REG_IS_GAIN_MAN__A, qpskIsGainMan, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EQ_REG_IS_GAIN_EXP__A, qpskIsGainExp, 0x0000);
				if (status < 0)
					break;
			}
			break;

		case QAM_16:
			transmissionParams |= SC_RA_RAM_OP_PARAM_CONST_QAM16;
			if (state->type_A) {
				status = Write16(state, EQ_REG_OT_CONST__A, 0x0001, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_CONST__A, EC_SB_REG_CONST_16QAM, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_SCALE_MSB__A, 0x0010, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_SCALE_BIT2__A, 0x0004, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EC_SB_REG_SCALE_LSB__A, 0x0000, 0x0000);
				if (status < 0)
					break;

				status = Write16(state, EQ_REG_TD_TPS_PWR_OFS__A, qam16TdTpsPwr, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EQ_REG_SN_CEGAIN__A, qam16SnCeGain, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EQ_REG_IS_GAIN_MAN__A, qam16IsGainMan, 0x0000);
				if (status < 0)
					break;
				status = Write16(state, EQ_REG_IS_GAIN_EXP__A, qam16IsGainExp, 0x0000);
				if (status < 0)
					break;
			}
			break;

		}
		if (status < 0)
			break;

		switch (DRX_CHANNEL_HIGH) {
		default:
		case DRX_CHANNEL_AUTO:
		case DRX_CHANNEL_LOW:
			transmissionParams |= SC_RA_RAM_OP_PARAM_PRIO_LO;
			status = Write16(state, EC_SB_REG_PRIOR__A, EC_SB_REG_PRIOR_LO, 0x0000);
			break;
		case DRX_CHANNEL_HIGH:
			transmissionParams |= SC_RA_RAM_OP_PARAM_PRIO_HI;
			status = Write16(state, EC_SB_REG_PRIOR__A, EC_SB_REG_PRIOR_HI, 0x0000);
			break;
		}

		switch (p->code_rate_HP) {
		case FEC_1_2:
			transmissionParams |= SC_RA_RAM_OP_PARAM_RATE_1_2;
			if (state->type_A)
				status = Write16(state, EC_VD_REG_SET_CODERATE__A, EC_VD_REG_SET_CODERATE_C1_2, 0x0000);
			break;
		default:
			operationMode |= SC_RA_RAM_OP_AUTO_RATE__M;
			/* fall through */
		case FEC_2_3:
			transmissionParams |= SC_RA_RAM_OP_PARAM_RATE_2_3;
			if (state->type_A)
				status = Write16(state, EC_VD_REG_SET_CODERATE__A, EC_VD_REG_SET_CODERATE_C2_3, 0x0000);
			break;
		case FEC_3_4:
			transmissionParams |= SC_RA_RAM_OP_PARAM_RATE_3_4;
			if (state->type_A)
				status = Write16(state, EC_VD_REG_SET_CODERATE__A, EC_VD_REG_SET_CODERATE_C3_4, 0x0000);
			break;
		case FEC_5_6:
			transmissionParams |= SC_RA_RAM_OP_PARAM_RATE_5_6;
			if (state->type_A)
				status = Write16(state, EC_VD_REG_SET_CODERATE__A, EC_VD_REG_SET_CODERATE_C5_6, 0x0000);
			break;
		case FEC_7_8:
			transmissionParams |= SC_RA_RAM_OP_PARAM_RATE_7_8;
			if (state->type_A)
				status = Write16(state, EC_VD_REG_SET_CODERATE__A, EC_VD_REG_SET_CODERATE_C7_8, 0x0000);
			break;
		}
		if (status < 0)
			break;

		/* First determine real bandwidth (Hz) */
		/* Also set delay for impulse noise cruncher (only A2) */
		/* Also set parameters for EC_OC fix, note
		   EC_OC_REG_TMD_HIL_MAR is changed
		   by SC for fix for some 8K,1/8 guard but is restored by
		   InitEC and ResetEC
		   functions */
		switch (p->bandwidth_hz) {
		case 0:
			p->bandwidth_hz = 8000000;
			/* fall through */
		case 8000000:
			/* (64/7)*(8/8)*1000000 */
			bandwidth = DRXD_BANDWIDTH_8MHZ_IN_HZ;

			bandwidthParam = 0;
			status = Write16(state,
					 FE_AG_REG_IND_DEL__A, 50, 0x0000);
			break;
		case 7000000:
			/* (64/7)*(7/8)*1000000 */
			bandwidth = DRXD_BANDWIDTH_7MHZ_IN_HZ;
			bandwidthParam = 0x4807;	/*binary:0100 1000 0000 0111 */
			status = Write16(state,
					 FE_AG_REG_IND_DEL__A, 59, 0x0000);
			break;
		case 6000000:
			/* (64/7)*(6/8)*1000000 */
			bandwidth = DRXD_BANDWIDTH_6MHZ_IN_HZ;
			bandwidthParam = 0x0F07;	/*binary: 0000 1111 0000 0111 */
			status = Write16(state,
					 FE_AG_REG_IND_DEL__A, 71, 0x0000);
			break;
		default:
			status = -EINVAL;
		}
		if (status < 0)
			break;

		status = Write16(state, SC_RA_RAM_BAND__A, bandwidthParam, 0x0000);
		if (status < 0)
			break;

		{
			u16 sc_config;
			status = Read16(state, SC_RA_RAM_CONFIG__A, &sc_config, 0);
			if (status < 0)
				break;

			/* enable SLAVE mode in 2k 1/32 to
			   prevent timing change glitches */
			if ((p->transmission_mode == TRANSMISSION_MODE_2K) &&
			    (p->guard_interval == GUARD_INTERVAL_1_32)) {
				/* enable slave */
				sc_config |= SC_RA_RAM_CONFIG_SLAVE__M;
			} else {
				/* disable slave */
				sc_config &= ~SC_RA_RAM_CONFIG_SLAVE__M;
			}
			status = Write16(state, SC_RA_RAM_CONFIG__A, sc_config, 0);
			if (status < 0)
				break;
		}

		status = SetCfgNoiseCalibration(state, &state->noise_cal);
		if (status < 0)
			break;

		if (state->cscd_state == CSCD_INIT) {
			/* switch on SRMM scan in SC */
			status = Write16(state, SC_RA_RAM_SAMPLE_RATE_COUNT__A, DRXD_OSCDEV_DO_SCAN, 0x0000);
			if (status < 0)
				break;
/*            CHK_ERROR(Write16(SC_RA_RAM_SAMPLE_RATE_STEP__A, DRXD_OSCDEV_STEP, 0x0000));*/
			state->cscd_state = CSCD_SET;
		}

		/* Now compute FE_IF_REG_INCR */
		/*((( SysFreq/BandWidth)/2)/2) -1) * 2^23) =>
		   ((SysFreq / BandWidth) * (2^21) ) - (2^23) */
		feIfIncr = MulDiv32(state->sys_clock_freq * 1000,
				    (1ULL << 21), bandwidth) - (1 << 23);
		status = Write16(state, FE_IF_REG_INCR0__A, (u16) (feIfIncr & FE_IF_REG_INCR0__M), 0x0000);
		if (status < 0)
			break;
		status = Write16(state, FE_IF_REG_INCR1__A, (u16) ((feIfIncr >> FE_IF_REG_INCR0__W) & FE_IF_REG_INCR1__M), 0x0000);
		if (status < 0)
			break;
		/* Bandwidth setting done */

		/* Mirror & frequency offset */
		SetFrequencyShift(state, off, mirrorFreqSpect);

		/* Start SC, write channel settings to SC */

		/* Enable SC after setting all other parameters */
		status = Write16(state, SC_COMM_STATE__A, 0, 0x0000);
		if (status < 0)
			break;
		status = Write16(state, SC_COMM_EXEC__A, 1, 0x0000);
		if (status < 0)
			break;

		/* Write SC parameter registers, operation mode */
#if 1
		operationMode = (SC_RA_RAM_OP_AUTO_MODE__M |
				 SC_RA_RAM_OP_AUTO_GUARD__M |
				 SC_RA_RAM_OP_AUTO_CONST__M |
				 SC_RA_RAM_OP_AUTO_HIER__M |
				 SC_RA_RAM_OP_AUTO_RATE__M);
#endif
		status = SC_SetPrefParamCommand(state, 0x0000, transmissionParams, operationMode);
		if (status < 0)
			break;

		/* Start correct processes to get in lock */
		status = SC_ProcStartCommand(state, SC_RA_RAM_PROC_LOCKTRACK, SC_RA_RAM_SW_EVENT_RUN_NMASK__M, SC_RA_RAM_LOCKTRACK_MIN);
		if (status < 0)
			break;

		status = StartOC(state);
		if (status < 0)
			break;

		if (state->operation_mode != OM_Default) {
			status = StartDiversity(state);
			if (status < 0)
				break;
		}

		state->drxd_state = DRXD_STARTED;
	} while (0);

	return status;
}