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
struct TYPE_8__ {int len; TYPE_1__* stat; } ;
struct TYPE_7__ {int len; TYPE_2__* stat; } ;
struct dtv_frontend_properties {TYPE_4__ cnr; TYPE_3__ strength; void* inversion; void* modulation; void* fec_inner; void* guard_interval; void* transmission_mode; } ;
struct cxd2880_priv {int /*<<< orphan*/  spi_mutex; int /*<<< orphan*/  tnrdmd; } ;
struct cxd2880_dvbt2_l1pre {int fft_mode; int gi; } ;
typedef  enum cxd2880_tnrdmd_spectrum_sense { ____Placeholder_cxd2880_tnrdmd_spectrum_sense } cxd2880_tnrdmd_spectrum_sense ;
typedef  enum cxd2880_dvbt2_plp_constell { ____Placeholder_cxd2880_dvbt2_plp_constell } cxd2880_dvbt2_plp_constell ;
typedef  enum cxd2880_dvbt2_plp_code_rate { ____Placeholder_cxd2880_dvbt2_plp_code_rate } cxd2880_dvbt2_plp_code_rate ;
struct TYPE_6__ {int svalue; void* scale; } ;
struct TYPE_5__ {void* scale; int /*<<< orphan*/  svalue; } ;

/* Variables and functions */
#define  CXD2880_DVBT2_G19_128 152 
#define  CXD2880_DVBT2_G19_256 151 
#define  CXD2880_DVBT2_G1_128 150 
#define  CXD2880_DVBT2_G1_16 149 
#define  CXD2880_DVBT2_G1_32 148 
#define  CXD2880_DVBT2_G1_4 147 
#define  CXD2880_DVBT2_G1_8 146 
#define  CXD2880_DVBT2_M16K 145 
#define  CXD2880_DVBT2_M1K 144 
#define  CXD2880_DVBT2_M2K 143 
#define  CXD2880_DVBT2_M32K 142 
#define  CXD2880_DVBT2_M4K 141 
#define  CXD2880_DVBT2_M8K 140 
 int /*<<< orphan*/  CXD2880_DVBT2_PLP_DATA ; 
#define  CXD2880_DVBT2_QAM16 139 
#define  CXD2880_DVBT2_QAM256 138 
#define  CXD2880_DVBT2_QAM64 137 
#define  CXD2880_DVBT2_QPSK 136 
#define  CXD2880_DVBT2_R1_2 135 
#define  CXD2880_DVBT2_R2_3 134 
#define  CXD2880_DVBT2_R3_4 133 
#define  CXD2880_DVBT2_R3_5 132 
#define  CXD2880_DVBT2_R4_5 131 
#define  CXD2880_DVBT2_R5_6 130 
#define  CXD2880_TNRDMD_SPECTRUM_INV 129 
#define  CXD2880_TNRDMD_SPECTRUM_NORMAL 128 
 int EINVAL ; 
 void* FEC_1_2 ; 
 void* FEC_2_3 ; 
 void* FEC_3_4 ; 
 void* FEC_3_5 ; 
 void* FEC_4_5 ; 
 void* FEC_5_6 ; 
 void* FEC_NONE ; 
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 void* GUARD_INTERVAL_19_128 ; 
 void* GUARD_INTERVAL_19_256 ; 
 void* GUARD_INTERVAL_1_128 ; 
 void* GUARD_INTERVAL_1_16 ; 
 void* GUARD_INTERVAL_1_32 ; 
 void* GUARD_INTERVAL_1_4 ; 
 void* GUARD_INTERVAL_1_8 ; 
 void* INVERSION_OFF ; 
 void* INVERSION_ON ; 
 void* QAM_16 ; 
 void* QAM_256 ; 
 void* QAM_64 ; 
 void* QPSK ; 
 void* TRANSMISSION_MODE_16K ; 
 void* TRANSMISSION_MODE_1K ; 
 void* TRANSMISSION_MODE_2K ; 
 void* TRANSMISSION_MODE_32K ; 
 void* TRANSMISSION_MODE_4K ; 
 void* TRANSMISSION_MODE_8K ; 
 int cxd2880_read_snr (struct dvb_frontend*,int /*<<< orphan*/ *) ; 
 int cxd2880_tnrdmd_dvbt2_mon_code_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int cxd2880_tnrdmd_dvbt2_mon_l1_pre (int /*<<< orphan*/ *,struct cxd2880_dvbt2_l1pre*) ; 
 int cxd2880_tnrdmd_dvbt2_mon_qam (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int cxd2880_tnrdmd_dvbt2_mon_spectrum_sense (int /*<<< orphan*/ *,int*) ; 
 int cxd2880_tnrdmd_mon_rf_lvl (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cxd2880_get_frontend_t2(struct dvb_frontend *fe,
				   struct dtv_frontend_properties *c)
{
	int ret;
	struct cxd2880_priv *priv = NULL;
	struct cxd2880_dvbt2_l1pre l1pre;
	enum cxd2880_dvbt2_plp_code_rate coderate;
	enum cxd2880_dvbt2_plp_constell qam;
	enum cxd2880_tnrdmd_spectrum_sense sense;
	u16 snr = 0;
	int strength = 0;

	if (!fe || !c) {
		pr_err("invalid arg.\n");
		return -EINVAL;
	}

	priv = fe->demodulator_priv;

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt2_mon_l1_pre(&priv->tnrdmd, &l1pre);
	mutex_unlock(priv->spi_mutex);
	if (!ret) {
		switch (l1pre.fft_mode) {
		case CXD2880_DVBT2_M2K:
			c->transmission_mode = TRANSMISSION_MODE_2K;
			break;
		case CXD2880_DVBT2_M8K:
			c->transmission_mode = TRANSMISSION_MODE_8K;
			break;
		case CXD2880_DVBT2_M4K:
			c->transmission_mode = TRANSMISSION_MODE_4K;
			break;
		case CXD2880_DVBT2_M1K:
			c->transmission_mode = TRANSMISSION_MODE_1K;
			break;
		case CXD2880_DVBT2_M16K:
			c->transmission_mode = TRANSMISSION_MODE_16K;
			break;
		case CXD2880_DVBT2_M32K:
			c->transmission_mode = TRANSMISSION_MODE_32K;
			break;
		default:
			c->transmission_mode = TRANSMISSION_MODE_2K;
			pr_debug("L1Pre fft_mode is invalid %d\n",
				 l1pre.fft_mode);
			break;
		}
		switch (l1pre.gi) {
		case CXD2880_DVBT2_G1_32:
			c->guard_interval = GUARD_INTERVAL_1_32;
			break;
		case CXD2880_DVBT2_G1_16:
			c->guard_interval = GUARD_INTERVAL_1_16;
			break;
		case CXD2880_DVBT2_G1_8:
			c->guard_interval = GUARD_INTERVAL_1_8;
			break;
		case CXD2880_DVBT2_G1_4:
			c->guard_interval = GUARD_INTERVAL_1_4;
			break;
		case CXD2880_DVBT2_G1_128:
			c->guard_interval = GUARD_INTERVAL_1_128;
			break;
		case CXD2880_DVBT2_G19_128:
			c->guard_interval = GUARD_INTERVAL_19_128;
			break;
		case CXD2880_DVBT2_G19_256:
			c->guard_interval = GUARD_INTERVAL_19_256;
			break;
		default:
			c->guard_interval = GUARD_INTERVAL_1_32;
			pr_debug("L1Pre guard interval is invalid %d\n",
				 l1pre.gi);
			break;
		}
	} else {
		c->transmission_mode = TRANSMISSION_MODE_2K;
		c->guard_interval = GUARD_INTERVAL_1_32;
		pr_debug("L1Pre err %d\n", ret);
	}

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt2_mon_code_rate(&priv->tnrdmd,
						 CXD2880_DVBT2_PLP_DATA,
						 &coderate);
	mutex_unlock(priv->spi_mutex);
	if (!ret) {
		switch (coderate) {
		case CXD2880_DVBT2_R1_2:
			c->fec_inner = FEC_1_2;
			break;
		case CXD2880_DVBT2_R3_5:
			c->fec_inner = FEC_3_5;
			break;
		case CXD2880_DVBT2_R2_3:
			c->fec_inner = FEC_2_3;
			break;
		case CXD2880_DVBT2_R3_4:
			c->fec_inner = FEC_3_4;
			break;
		case CXD2880_DVBT2_R4_5:
			c->fec_inner = FEC_4_5;
			break;
		case CXD2880_DVBT2_R5_6:
			c->fec_inner = FEC_5_6;
			break;
		default:
			c->fec_inner = FEC_NONE;
			pr_debug("CodeRate is invalid %d\n", coderate);
			break;
		}
	} else {
		c->fec_inner = FEC_NONE;
		pr_debug("CodeRate %d\n", ret);
	}

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt2_mon_qam(&priv->tnrdmd,
					   CXD2880_DVBT2_PLP_DATA,
					   &qam);
	mutex_unlock(priv->spi_mutex);
	if (!ret) {
		switch (qam) {
		case CXD2880_DVBT2_QPSK:
			c->modulation = QPSK;
			break;
		case CXD2880_DVBT2_QAM16:
			c->modulation = QAM_16;
			break;
		case CXD2880_DVBT2_QAM64:
			c->modulation = QAM_64;
			break;
		case CXD2880_DVBT2_QAM256:
			c->modulation = QAM_256;
			break;
		default:
			c->modulation = QPSK;
			pr_debug("QAM is invalid %d\n", qam);
			break;
		}
	} else {
		c->modulation = QPSK;
		pr_debug("QAM %d\n", ret);
	}

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt2_mon_spectrum_sense(&priv->tnrdmd, &sense);
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
		pr_debug("SpectrumSense %d\n", ret);
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