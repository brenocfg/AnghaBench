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
struct dvb_frontend {struct dib3000_state* demodulator_priv; } ;
struct dtv_frontend_properties {int code_rate_LP; int code_rate_HP; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  guard_interval; void* hierarchy; int /*<<< orphan*/  modulation; int /*<<< orphan*/  inversion; } ;
struct dib3000_state {int dummy; } ;
typedef  enum fe_code_rate { ____Placeholder_fe_code_rate } fe_code_rate ;

/* Variables and functions */
 int /*<<< orphan*/  DIB3000MB_REG_DDS_FREQ_LSB ; 
 int /*<<< orphan*/  DIB3000MB_REG_DDS_FREQ_MSB ; 
 int /*<<< orphan*/  DIB3000MB_REG_DDS_VALUE_LSB ; 
 int /*<<< orphan*/  DIB3000MB_REG_DDS_VALUE_MSB ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_CODE_RATE_HP ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_CODE_RATE_LP ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_FFT ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_GUARD_TIME ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_HRCH ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_LOCK ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_QAM ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_VIT_ALPHA ; 
#define  DIB3000_ALPHA_0 145 
#define  DIB3000_ALPHA_1 144 
#define  DIB3000_ALPHA_2 143 
#define  DIB3000_ALPHA_4 142 
#define  DIB3000_CONSTELLATION_16QAM 141 
#define  DIB3000_CONSTELLATION_64QAM 140 
#define  DIB3000_CONSTELLATION_QPSK 139 
#define  DIB3000_FEC_1_2 138 
#define  DIB3000_FEC_2_3 137 
#define  DIB3000_FEC_3_4 136 
#define  DIB3000_FEC_5_6 135 
#define  DIB3000_FEC_7_8 134 
#define  DIB3000_GUARD_TIME_1_16 133 
#define  DIB3000_GUARD_TIME_1_32 132 
#define  DIB3000_GUARD_TIME_1_4 131 
#define  DIB3000_GUARD_TIME_1_8 130 
#define  DIB3000_TRANSMISSION_MODE_2K 129 
#define  DIB3000_TRANSMISSION_MODE_8K 128 
 int FEC_1_2 ; 
 int FEC_2_3 ; 
 int FEC_3_4 ; 
 int FEC_4_5 ; 
 int FEC_7_8 ; 
 void* FEC_NONE ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_16 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_8 ; 
 void* HIERARCHY_1 ; 
 void* HIERARCHY_2 ; 
 void* HIERARCHY_4 ; 
 void* HIERARCHY_NONE ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int /*<<< orphan*/  deb_getf (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int rd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib3000mb_get_frontend(struct dvb_frontend* fe,
				  struct dtv_frontend_properties *c)
{
	struct dib3000_state* state = fe->demodulator_priv;
	enum fe_code_rate *cr;
	u16 tps_val;
	int inv_test1,inv_test2;
	u32 dds_val, threshold = 0x800000;

	if (!rd(DIB3000MB_REG_TPS_LOCK))
		return 0;

	dds_val = ((rd(DIB3000MB_REG_DDS_VALUE_MSB) & 0xff) << 16) + rd(DIB3000MB_REG_DDS_VALUE_LSB);
	deb_getf("DDS_VAL: %x %x %x\n", dds_val, rd(DIB3000MB_REG_DDS_VALUE_MSB), rd(DIB3000MB_REG_DDS_VALUE_LSB));
	if (dds_val < threshold)
		inv_test1 = 0;
	else if (dds_val == threshold)
		inv_test1 = 1;
	else
		inv_test1 = 2;

	dds_val = ((rd(DIB3000MB_REG_DDS_FREQ_MSB) & 0xff) << 16) + rd(DIB3000MB_REG_DDS_FREQ_LSB);
	deb_getf("DDS_FREQ: %x %x %x\n", dds_val, rd(DIB3000MB_REG_DDS_FREQ_MSB), rd(DIB3000MB_REG_DDS_FREQ_LSB));
	if (dds_val < threshold)
		inv_test2 = 0;
	else if (dds_val == threshold)
		inv_test2 = 1;
	else
		inv_test2 = 2;

	c->inversion =
		((inv_test2 == 2) && (inv_test1==1 || inv_test1==0)) ||
		((inv_test2 == 0) && (inv_test1==1 || inv_test1==2)) ?
		INVERSION_ON : INVERSION_OFF;

	deb_getf("inversion %d %d, %d\n", inv_test2, inv_test1, c->inversion);

	switch ((tps_val = rd(DIB3000MB_REG_TPS_QAM))) {
		case DIB3000_CONSTELLATION_QPSK:
			deb_getf("QPSK\n");
			c->modulation = QPSK;
			break;
		case DIB3000_CONSTELLATION_16QAM:
			deb_getf("QAM16\n");
			c->modulation = QAM_16;
			break;
		case DIB3000_CONSTELLATION_64QAM:
			deb_getf("QAM64\n");
			c->modulation = QAM_64;
			break;
		default:
			pr_err("Unexpected constellation returned by TPS (%d)\n", tps_val);
			break;
	}
	deb_getf("TPS: %d\n", tps_val);

	if (rd(DIB3000MB_REG_TPS_HRCH)) {
		deb_getf("HRCH ON\n");
		cr = &c->code_rate_LP;
		c->code_rate_HP = FEC_NONE;
		switch ((tps_val = rd(DIB3000MB_REG_TPS_VIT_ALPHA))) {
			case DIB3000_ALPHA_0:
				deb_getf("HIERARCHY_NONE\n");
				c->hierarchy = HIERARCHY_NONE;
				break;
			case DIB3000_ALPHA_1:
				deb_getf("HIERARCHY_1\n");
				c->hierarchy = HIERARCHY_1;
				break;
			case DIB3000_ALPHA_2:
				deb_getf("HIERARCHY_2\n");
				c->hierarchy = HIERARCHY_2;
				break;
			case DIB3000_ALPHA_4:
				deb_getf("HIERARCHY_4\n");
				c->hierarchy = HIERARCHY_4;
				break;
			default:
				pr_err("Unexpected ALPHA value returned by TPS (%d)\n", tps_val);
				break;
		}
		deb_getf("TPS: %d\n", tps_val);

		tps_val = rd(DIB3000MB_REG_TPS_CODE_RATE_LP);
	} else {
		deb_getf("HRCH OFF\n");
		cr = &c->code_rate_HP;
		c->code_rate_LP = FEC_NONE;
		c->hierarchy = HIERARCHY_NONE;

		tps_val = rd(DIB3000MB_REG_TPS_CODE_RATE_HP);
	}

	switch (tps_val) {
		case DIB3000_FEC_1_2:
			deb_getf("FEC_1_2\n");
			*cr = FEC_1_2;
			break;
		case DIB3000_FEC_2_3:
			deb_getf("FEC_2_3\n");
			*cr = FEC_2_3;
			break;
		case DIB3000_FEC_3_4:
			deb_getf("FEC_3_4\n");
			*cr = FEC_3_4;
			break;
		case DIB3000_FEC_5_6:
			deb_getf("FEC_5_6\n");
			*cr = FEC_4_5;
			break;
		case DIB3000_FEC_7_8:
			deb_getf("FEC_7_8\n");
			*cr = FEC_7_8;
			break;
		default:
			pr_err("Unexpected FEC returned by TPS (%d)\n", tps_val);
			break;
	}
	deb_getf("TPS: %d\n",tps_val);

	switch ((tps_val = rd(DIB3000MB_REG_TPS_GUARD_TIME))) {
		case DIB3000_GUARD_TIME_1_32:
			deb_getf("GUARD_INTERVAL_1_32\n");
			c->guard_interval = GUARD_INTERVAL_1_32;
			break;
		case DIB3000_GUARD_TIME_1_16:
			deb_getf("GUARD_INTERVAL_1_16\n");
			c->guard_interval = GUARD_INTERVAL_1_16;
			break;
		case DIB3000_GUARD_TIME_1_8:
			deb_getf("GUARD_INTERVAL_1_8\n");
			c->guard_interval = GUARD_INTERVAL_1_8;
			break;
		case DIB3000_GUARD_TIME_1_4:
			deb_getf("GUARD_INTERVAL_1_4\n");
			c->guard_interval = GUARD_INTERVAL_1_4;
			break;
		default:
			pr_err("Unexpected Guard Time returned by TPS (%d)\n", tps_val);
			break;
	}
	deb_getf("TPS: %d\n", tps_val);

	switch ((tps_val = rd(DIB3000MB_REG_TPS_FFT))) {
		case DIB3000_TRANSMISSION_MODE_2K:
			deb_getf("TRANSMISSION_MODE_2K\n");
			c->transmission_mode = TRANSMISSION_MODE_2K;
			break;
		case DIB3000_TRANSMISSION_MODE_8K:
			deb_getf("TRANSMISSION_MODE_8K\n");
			c->transmission_mode = TRANSMISSION_MODE_8K;
			break;
		default:
			pr_err("unexpected transmission mode return by TPS (%d)\n", tps_val);
			break;
	}
	deb_getf("TPS: %d\n", tps_val);

	return 0;
}