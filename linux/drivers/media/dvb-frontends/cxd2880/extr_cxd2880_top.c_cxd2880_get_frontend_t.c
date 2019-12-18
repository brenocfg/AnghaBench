#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {struct cxd2880_priv* demodulator_priv; } ;
struct TYPE_6__ {int len; TYPE_1__* stat; } ;
struct TYPE_8__ {int len; TYPE_3__* stat; } ;
struct dtv_frontend_properties {TYPE_2__ cnr; TYPE_4__ strength; void* inversion; void* modulation; void* code_rate_LP; void* code_rate_HP; void* hierarchy; void* guard_interval; void* transmission_mode; } ;
struct cxd2880_priv {int /*<<< orphan*/  spi_mutex; int /*<<< orphan*/  tnrdmd; } ;
struct cxd2880_dvbt_tpsinfo {int hierarchy; int rate_hp; int rate_lp; int constellation; } ;
typedef  enum cxd2880_tnrdmd_spectrum_sense { ____Placeholder_cxd2880_tnrdmd_spectrum_sense } cxd2880_tnrdmd_spectrum_sense ;
typedef  enum cxd2880_dvbt_mode { ____Placeholder_cxd2880_dvbt_mode } cxd2880_dvbt_mode ;
typedef  enum cxd2880_dvbt_guard { ____Placeholder_cxd2880_dvbt_guard } cxd2880_dvbt_guard ;
struct TYPE_7__ {int svalue; void* scale; } ;
struct TYPE_5__ {void* scale; int /*<<< orphan*/  svalue; } ;

/* Variables and functions */
#define  CXD2880_DVBT_CODERATE_1_2 147 
#define  CXD2880_DVBT_CODERATE_2_3 146 
#define  CXD2880_DVBT_CODERATE_3_4 145 
#define  CXD2880_DVBT_CODERATE_5_6 144 
#define  CXD2880_DVBT_CODERATE_7_8 143 
#define  CXD2880_DVBT_CONSTELLATION_16QAM 142 
#define  CXD2880_DVBT_CONSTELLATION_64QAM 141 
#define  CXD2880_DVBT_CONSTELLATION_QPSK 140 
#define  CXD2880_DVBT_GUARD_1_16 139 
#define  CXD2880_DVBT_GUARD_1_32 138 
#define  CXD2880_DVBT_GUARD_1_4 137 
#define  CXD2880_DVBT_GUARD_1_8 136 
#define  CXD2880_DVBT_HIERARCHY_1 135 
#define  CXD2880_DVBT_HIERARCHY_2 134 
#define  CXD2880_DVBT_HIERARCHY_4 133 
#define  CXD2880_DVBT_HIERARCHY_NON 132 
#define  CXD2880_DVBT_MODE_2K 131 
#define  CXD2880_DVBT_MODE_8K 130 
#define  CXD2880_TNRDMD_SPECTRUM_INV 129 
#define  CXD2880_TNRDMD_SPECTRUM_NORMAL 128 
 int EINVAL ; 
 void* FEC_1_2 ; 
 void* FEC_2_3 ; 
 void* FEC_3_4 ; 
 void* FEC_5_6 ; 
 void* FEC_7_8 ; 
 void* FEC_NONE ; 
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 void* GUARD_INTERVAL_1_16 ; 
 void* GUARD_INTERVAL_1_32 ; 
 void* GUARD_INTERVAL_1_4 ; 
 void* GUARD_INTERVAL_1_8 ; 
 void* HIERARCHY_1 ; 
 void* HIERARCHY_2 ; 
 void* HIERARCHY_4 ; 
 void* HIERARCHY_NONE ; 
 void* INVERSION_OFF ; 
 void* INVERSION_ON ; 
 void* QAM_16 ; 
 void* QAM_64 ; 
 void* QPSK ; 
 void* TRANSMISSION_MODE_2K ; 
 void* TRANSMISSION_MODE_8K ; 
 int cxd2880_read_snr (struct dvb_frontend*,int /*<<< orphan*/ *) ; 
 int cxd2880_tnrdmd_dvbt_mon_mode_guard (int /*<<< orphan*/ *,int*,int*) ; 
 int cxd2880_tnrdmd_dvbt_mon_spectrum_sense (int /*<<< orphan*/ *,int*) ; 
 int cxd2880_tnrdmd_dvbt_mon_tps_info (int /*<<< orphan*/ *,struct cxd2880_dvbt_tpsinfo*) ; 
 int cxd2880_tnrdmd_mon_rf_lvl (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cxd2880_get_frontend_t(struct dvb_frontend *fe,
				  struct dtv_frontend_properties *c)
{
	int ret;
	struct cxd2880_priv *priv = NULL;
	enum cxd2880_dvbt_mode mode = CXD2880_DVBT_MODE_2K;
	enum cxd2880_dvbt_guard guard = CXD2880_DVBT_GUARD_1_32;
	struct cxd2880_dvbt_tpsinfo tps;
	enum cxd2880_tnrdmd_spectrum_sense sense;
	u16 snr = 0;
	int strength = 0;

	if (!fe || !c) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}

	priv = fe->demodulator_priv;

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt_mon_mode_guard(&priv->tnrdmd,
						 &mode, &guard);
	mutex_unlock(priv->spi_mutex);
	if (!ret) {
		switch (mode) {
		case CXD2880_DVBT_MODE_2K:
			c->transmission_mode = TRANSMISSION_MODE_2K;
			break;
		case CXD2880_DVBT_MODE_8K:
			c->transmission_mode = TRANSMISSION_MODE_8K;
			break;
		default:
			c->transmission_mode = TRANSMISSION_MODE_2K;
			pr_debug("transmission mode is invalid %d\n", mode);
			break;
		}
		switch (guard) {
		case CXD2880_DVBT_GUARD_1_32:
			c->guard_interval = GUARD_INTERVAL_1_32;
			break;
		case CXD2880_DVBT_GUARD_1_16:
			c->guard_interval = GUARD_INTERVAL_1_16;
			break;
		case CXD2880_DVBT_GUARD_1_8:
			c->guard_interval = GUARD_INTERVAL_1_8;
			break;
		case CXD2880_DVBT_GUARD_1_4:
			c->guard_interval = GUARD_INTERVAL_1_4;
			break;
		default:
			c->guard_interval = GUARD_INTERVAL_1_32;
			pr_debug("guard interval is invalid %d\n",
				 guard);
			break;
		}
	} else {
		c->transmission_mode = TRANSMISSION_MODE_2K;
		c->guard_interval = GUARD_INTERVAL_1_32;
		pr_debug("ModeGuard err %d\n", ret);
	}

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt_mon_tps_info(&priv->tnrdmd, &tps);
	mutex_unlock(priv->spi_mutex);
	if (!ret) {
		switch (tps.hierarchy) {
		case CXD2880_DVBT_HIERARCHY_NON:
			c->hierarchy = HIERARCHY_NONE;
			break;
		case CXD2880_DVBT_HIERARCHY_1:
			c->hierarchy = HIERARCHY_1;
			break;
		case CXD2880_DVBT_HIERARCHY_2:
			c->hierarchy = HIERARCHY_2;
			break;
		case CXD2880_DVBT_HIERARCHY_4:
			c->hierarchy = HIERARCHY_4;
			break;
		default:
			c->hierarchy = HIERARCHY_NONE;
			pr_debug("TPSInfo hierarchy is invalid %d\n",
				 tps.hierarchy);
			break;
		}

		switch (tps.rate_hp) {
		case CXD2880_DVBT_CODERATE_1_2:
			c->code_rate_HP = FEC_1_2;
			break;
		case CXD2880_DVBT_CODERATE_2_3:
			c->code_rate_HP = FEC_2_3;
			break;
		case CXD2880_DVBT_CODERATE_3_4:
			c->code_rate_HP = FEC_3_4;
			break;
		case CXD2880_DVBT_CODERATE_5_6:
			c->code_rate_HP = FEC_5_6;
			break;
		case CXD2880_DVBT_CODERATE_7_8:
			c->code_rate_HP = FEC_7_8;
			break;
		default:
			c->code_rate_HP = FEC_NONE;
			pr_debug("TPSInfo rateHP is invalid %d\n",
				 tps.rate_hp);
			break;
		}
		switch (tps.rate_lp) {
		case CXD2880_DVBT_CODERATE_1_2:
			c->code_rate_LP = FEC_1_2;
			break;
		case CXD2880_DVBT_CODERATE_2_3:
			c->code_rate_LP = FEC_2_3;
			break;
		case CXD2880_DVBT_CODERATE_3_4:
			c->code_rate_LP = FEC_3_4;
			break;
		case CXD2880_DVBT_CODERATE_5_6:
			c->code_rate_LP = FEC_5_6;
			break;
		case CXD2880_DVBT_CODERATE_7_8:
			c->code_rate_LP = FEC_7_8;
			break;
		default:
			c->code_rate_LP = FEC_NONE;
			pr_debug("TPSInfo rateLP is invalid %d\n",
				 tps.rate_lp);
			break;
		}
		switch (tps.constellation) {
		case CXD2880_DVBT_CONSTELLATION_QPSK:
			c->modulation = QPSK;
			break;
		case CXD2880_DVBT_CONSTELLATION_16QAM:
			c->modulation = QAM_16;
			break;
		case CXD2880_DVBT_CONSTELLATION_64QAM:
			c->modulation = QAM_64;
			break;
		default:
			c->modulation = QPSK;
			pr_debug("TPSInfo constellation is invalid %d\n",
				 tps.constellation);
			break;
		}
	} else {
		c->hierarchy = HIERARCHY_NONE;
		c->code_rate_HP = FEC_NONE;
		c->code_rate_LP = FEC_NONE;
		c->modulation = QPSK;
		pr_debug("TPS info err %d\n", ret);
	}

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt_mon_spectrum_sense(&priv->tnrdmd, &sense);
	mutex_unlock(priv->spi_mutex);
	if (!ret) {
		switch (sense) {
		case CXD2880_TNRDMD_SPECTRUM_NORMAL:
			c->inversion = INVERSION_OFF;
			break;
		case CXD2880_TNRDMD_SPECTRUM_INV:
			c->inversion = INVERSION_ON;
			break;
		default:
			c->inversion = INVERSION_OFF;
			pr_debug("spectrum sense is invalid %d\n", sense);
			break;
		}
	} else {
		c->inversion = INVERSION_OFF;
		pr_debug("spectrum_sense %d\n", ret);
	}

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_mon_rf_lvl(&priv->tnrdmd, &strength);
	mutex_unlock(priv->spi_mutex);
	if (!ret) {
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_DECIBEL;
		c->strength.stat[0].svalue = strength;
	} else {
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		pr_debug("mon_rf_lvl %d\n", ret);
	}

	ret = cxd2880_read_snr(fe, &snr);
	if (!ret) {
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = snr;
	} else {
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		pr_debug("read_snr %d\n", ret);
	}

	return 0;
}