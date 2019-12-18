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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int IF; scalar_t__ (* osc_deviation ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct drxd_state {int init_done; long expected_sys_clock_freq; int microcode_length; int /*<<< orphan*/  drxd_state; int /*<<< orphan*/  cscd_state; int /*<<< orphan*/  rf_agc_cfg; int /*<<< orphan*/  if_agc_cfg; int /*<<< orphan*/  m_FeAgRegAgAgcSio; int /*<<< orphan*/  m_FeAgRegAgPwd; scalar_t__ PGA; int /*<<< orphan*/  const* microcode; scalar_t__ type_A; scalar_t__ sys_clock_freq; scalar_t__ osc_clock_deviation; int /*<<< orphan*/  priv; TYPE_1__ config; scalar_t__ m_HiI2cPatch; int /*<<< orphan*/  operation_mode; } ;
typedef  long s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CDRXD (struct drxd_state*,int) ; 
 int /*<<< orphan*/  CSCD_INIT ; 
 int /*<<< orphan*/  DRXD_DEF_AG_AGC_SIO ; 
 int /*<<< orphan*/  DRXD_DEF_AG_PWD_CONSUMER ; 
 int /*<<< orphan*/  DRXD_DEF_AG_PWD_PRO ; 
 int /*<<< orphan*/  DRXD_STOPPED ; 
 int DownloadMicrocode (struct drxd_state*,int /*<<< orphan*/  const*,int) ; 
 int EnableAndResetMB (struct drxd_state*) ; 
 int HI_ResetCommand (struct drxd_state*) ; 
 int InitAtomicRead (struct drxd_state*) ; 
 int InitCC (struct drxd_state*) ; 
 int InitCE (struct drxd_state*) ; 
 int InitCP (struct drxd_state*) ; 
 int InitEC (struct drxd_state*) ; 
 int InitEQ (struct drxd_state*) ; 
 int InitFE (struct drxd_state*) ; 
 int InitFT (struct drxd_state*) ; 
 int InitHI (struct drxd_state*) ; 
 int InitSC (struct drxd_state*) ; 
 int LC_COMM_EXEC__A ; 
 int /*<<< orphan*/  OM_Default ; 
 int ResetCEFR (struct drxd_state*) ; 
 int SC_COMM_EXEC_CTL_STOP ; 
 int SC_COMM_EXEC__A ; 
 int /*<<< orphan*/  SC_RA_RAM_DRIVER_VERSION__AX ; 
 int SetCfgIfAgc (struct drxd_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetCfgPga (struct drxd_state*,int /*<<< orphan*/ ) ; 
 int SetCfgRfAgc (struct drxd_state*,int /*<<< orphan*/ *) ; 
 int SetDeviceTypeId (struct drxd_state*) ; 
 int StopAllProcessors (struct drxd_state*) ; 
 int StopOC (struct drxd_state*) ; 
 int VERSION_MAJOR ; 
 int VERSION_MINOR ; 
 int VERSION_PATCH ; 
 int Write16 (struct drxd_state*,int,int,int /*<<< orphan*/ ) ; 
 int Write32 (struct drxd_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int WriteTable (struct drxd_state*,scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DRXD_init(struct drxd_state *state, const u8 *fw, u32 fw_size)
{
	int status = 0;
	u32 driverVersion;

	if (state->init_done)
		return 0;

	CDRXD(state, state->config.IF ? state->config.IF : 36000000);

	do {
		state->operation_mode = OM_Default;

		status = SetDeviceTypeId(state);
		if (status < 0)
			break;

		/* Apply I2c address patch to B1 */
		if (!state->type_A && state->m_HiI2cPatch) {
			status = WriteTable(state, state->m_HiI2cPatch);
			if (status < 0)
				break;
		}

		if (state->type_A) {
			/* HI firmware patch for UIO readout,
			   avoid clearing of result register */
			status = Write16(state, 0x43012D, 0x047f, 0);
			if (status < 0)
				break;
		}

		status = HI_ResetCommand(state);
		if (status < 0)
			break;

		status = StopAllProcessors(state);
		if (status < 0)
			break;
		status = InitCC(state);
		if (status < 0)
			break;

		state->osc_clock_deviation = 0;

		if (state->config.osc_deviation)
			state->osc_clock_deviation =
			    state->config.osc_deviation(state->priv, 0, 0);
		{
			/* Handle clock deviation */
			s32 devB;
			s32 devA = (s32) (state->osc_clock_deviation) *
			    (s32) (state->expected_sys_clock_freq);
			/* deviation in kHz */
			s32 deviation = (devA / (1000000L));
			/* rounding, signed */
			if (devA > 0)
				devB = (2);
			else
				devB = (-2);
			if ((devB * (devA % 1000000L) > 1000000L)) {
				/* add +1 or -1 */
				deviation += (devB / 2);
			}

			state->sys_clock_freq =
			    (u16) ((state->expected_sys_clock_freq) +
				   deviation);
		}
		status = InitHI(state);
		if (status < 0)
			break;
		status = InitAtomicRead(state);
		if (status < 0)
			break;

		status = EnableAndResetMB(state);
		if (status < 0)
			break;
		if (state->type_A) {
			status = ResetCEFR(state);
			if (status < 0)
				break;
		}
		if (fw) {
			status = DownloadMicrocode(state, fw, fw_size);
			if (status < 0)
				break;
		} else {
			status = DownloadMicrocode(state, state->microcode, state->microcode_length);
			if (status < 0)
				break;
		}

		if (state->PGA) {
			state->m_FeAgRegAgPwd = DRXD_DEF_AG_PWD_PRO;
			SetCfgPga(state, 0);	/* PGA = 0 dB */
		} else {
			state->m_FeAgRegAgPwd = DRXD_DEF_AG_PWD_CONSUMER;
		}

		state->m_FeAgRegAgAgcSio = DRXD_DEF_AG_AGC_SIO;

		status = InitFE(state);
		if (status < 0)
			break;
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
		status = InitEC(state);
		if (status < 0)
			break;
		status = InitSC(state);
		if (status < 0)
			break;

		status = SetCfgIfAgc(state, &state->if_agc_cfg);
		if (status < 0)
			break;
		status = SetCfgRfAgc(state, &state->rf_agc_cfg);
		if (status < 0)
			break;

		state->cscd_state = CSCD_INIT;
		status = Write16(state, SC_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
		if (status < 0)
			break;
		status = Write16(state, LC_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
		if (status < 0)
			break;

		driverVersion = (((VERSION_MAJOR / 10) << 4) +
				 (VERSION_MAJOR % 10)) << 24;
		driverVersion += (((VERSION_MINOR / 10) << 4) +
				  (VERSION_MINOR % 10)) << 16;
		driverVersion += ((VERSION_PATCH / 1000) << 12) +
		    ((VERSION_PATCH / 100) << 8) +
		    ((VERSION_PATCH / 10) << 4) + (VERSION_PATCH % 10);

		status = Write32(state, SC_RA_RAM_DRIVER_VERSION__AX, driverVersion, 0);
		if (status < 0)
			break;

		status = StopOC(state);
		if (status < 0)
			break;

		state->drxd_state = DRXD_STOPPED;
		state->init_done = 1;
		status = 0;
	} while (0);
	return status;
}