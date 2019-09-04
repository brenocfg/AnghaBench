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
struct i2c_device_addr {int dummy; } ;
struct drxj_data {int fec_bits_desired; int fec_rs_prescale; int standard; int fec_rs_plen; int fec_rs_period; int fec_vd_plen; int qam_vd_prescale; int qam_vd_period; } ;
struct drx_demod_instance {scalar_t__ my_ext_attr; struct i2c_device_addr* my_i2c_dev_addr; } ;
typedef  enum drx_modulation { ____Placeholder_drx_modulation } drx_modulation ;

/* Variables and functions */
#define  DRX_CONSTELLATION_QAM128 135 
#define  DRX_CONSTELLATION_QAM16 134 
#define  DRX_CONSTELLATION_QAM256 133 
#define  DRX_CONSTELLATION_QAM32 132 
#define  DRX_CONSTELLATION_QAM64 131 
#define  DRX_STANDARD_ITU_A 130 
#define  DRX_STANDARD_ITU_B 129 
#define  DRX_STANDARD_ITU_C 128 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FEC_OC_SNC_FAIL_PERIOD__A ; 
 int /*<<< orphan*/  FEC_RS_MEASUREMENT_PERIOD__A ; 
 int /*<<< orphan*/  FEC_RS_MEASUREMENT_PRESCALE__A ; 
 int /*<<< orphan*/  QAM_TOP_CONSTELLATION_QAM256 ; 
 int /*<<< orphan*/  QAM_TOP_CONSTELLATION_QAM64 ; 
 int /*<<< orphan*/  QAM_VD_MEASUREMENT_PERIOD__A ; 
 int /*<<< orphan*/  QAM_VD_MEASUREMENT_PRESCALE__A ; 
 int /*<<< orphan*/  SCU_RAM_FEC_ACCUM_CW_CORRECTED_LO__A ; 
 int /*<<< orphan*/  SCU_RAM_FEC_ACCUM_PKT_FAILURES__A ; 
 int /*<<< orphan*/  SCU_RAM_FEC_MEAS_COUNT__A ; 
 int drxdap_fasi_write_reg32 (struct i2c_device_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int
set_qam_measurement(struct drx_demod_instance *demod,
		    enum drx_modulation constellation, u32 symbol_rate)
{
	struct i2c_device_addr *dev_addr = NULL;	/* device address for I2C writes */
	struct drxj_data *ext_attr = NULL;	/* Global data container for DRXJ specific data */
	int rc;
	u32 fec_bits_desired = 0;	/* BER accounting period */
	u16 fec_rs_plen = 0;	/* defines RS BER measurement period */
	u16 fec_rs_prescale = 0;	/* ReedSolomon Measurement Prescale */
	u32 fec_rs_period = 0;	/* Value for corresponding I2C register */
	u32 fec_rs_bit_cnt = 0;	/* Actual precise amount of bits */
	u32 fec_oc_snc_fail_period = 0;	/* Value for corresponding I2C register */
	u32 qam_vd_period = 0;	/* Value for corresponding I2C register */
	u32 qam_vd_bit_cnt = 0;	/* Actual precise amount of bits */
	u16 fec_vd_plen = 0;	/* no of trellis symbols: VD SER measur period */
	u16 qam_vd_prescale = 0;	/* Viterbi Measurement Prescale */

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (struct drxj_data *) demod->my_ext_attr;

	fec_bits_desired = ext_attr->fec_bits_desired;
	fec_rs_prescale = ext_attr->fec_rs_prescale;

	switch (constellation) {
	case DRX_CONSTELLATION_QAM16:
		fec_bits_desired = 4 * symbol_rate;
		break;
	case DRX_CONSTELLATION_QAM32:
		fec_bits_desired = 5 * symbol_rate;
		break;
	case DRX_CONSTELLATION_QAM64:
		fec_bits_desired = 6 * symbol_rate;
		break;
	case DRX_CONSTELLATION_QAM128:
		fec_bits_desired = 7 * symbol_rate;
		break;
	case DRX_CONSTELLATION_QAM256:
		fec_bits_desired = 8 * symbol_rate;
		break;
	default:
		return -EINVAL;
	}

	/* Parameters for Reed-Solomon Decoder */
	/* fecrs_period = (int)ceil(FEC_BITS_DESIRED/(fecrs_prescale*plen)) */
	/* rs_bit_cnt   = fecrs_period*fecrs_prescale*plen                  */
	/*     result is within 32 bit arithmetic ->                        */
	/*     no need for mult or frac functions                           */

	/* TODO: use constant instead of calculation and remove the fec_rs_plen in ext_attr */
	switch (ext_attr->standard) {
	case DRX_STANDARD_ITU_A:
	case DRX_STANDARD_ITU_C:
		fec_rs_plen = 204 * 8;
		break;
	case DRX_STANDARD_ITU_B:
		fec_rs_plen = 128 * 7;
		break;
	default:
		return -EINVAL;
	}

	ext_attr->fec_rs_plen = fec_rs_plen;	/* for getSigQual */
	fec_rs_bit_cnt = fec_rs_prescale * fec_rs_plen;	/* temp storage   */
	if (fec_rs_bit_cnt == 0) {
		pr_err("error: fec_rs_bit_cnt is zero!\n");
		return -EIO;
	}
	fec_rs_period = fec_bits_desired / fec_rs_bit_cnt + 1;	/* ceil */
	if (ext_attr->standard != DRX_STANDARD_ITU_B)
		fec_oc_snc_fail_period = fec_rs_period;

	/* limit to max 16 bit value (I2C register width) if needed */
	if (fec_rs_period > 0xFFFF)
		fec_rs_period = 0xFFFF;

	/* write corresponding registers */
	switch (ext_attr->standard) {
	case DRX_STANDARD_ITU_A:
	case DRX_STANDARD_ITU_C:
		break;
	case DRX_STANDARD_ITU_B:
		switch (constellation) {
		case DRX_CONSTELLATION_QAM64:
			fec_rs_period = 31581;
			fec_oc_snc_fail_period = 17932;
			break;
		case DRX_CONSTELLATION_QAM256:
			fec_rs_period = 45446;
			fec_oc_snc_fail_period = 25805;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	rc = drxj_dap_write_reg16(dev_addr, FEC_OC_SNC_FAIL_PERIOD__A, (u16)fec_oc_snc_fail_period, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, FEC_RS_MEASUREMENT_PERIOD__A, (u16)fec_rs_period, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, FEC_RS_MEASUREMENT_PRESCALE__A, fec_rs_prescale, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	ext_attr->fec_rs_period = (u16) fec_rs_period;
	ext_attr->fec_rs_prescale = fec_rs_prescale;
	rc = drxdap_fasi_write_reg32(dev_addr, SCU_RAM_FEC_ACCUM_CW_CORRECTED_LO__A, 0, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_FEC_MEAS_COUNT__A, 0, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, SCU_RAM_FEC_ACCUM_PKT_FAILURES__A, 0, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	if (ext_attr->standard == DRX_STANDARD_ITU_B) {
		/* Parameters for Viterbi Decoder */
		/* qamvd_period = (int)ceil(FEC_BITS_DESIRED/                      */
		/*                    (qamvd_prescale*plen*(qam_constellation+1))) */
		/* vd_bit_cnt   = qamvd_period*qamvd_prescale*plen                 */
		/*     result is within 32 bit arithmetic ->                       */
		/*     no need for mult or frac functions                          */

		/* a(8 bit) * b(8 bit) = 16 bit result => mult32 not needed */
		fec_vd_plen = ext_attr->fec_vd_plen;
		qam_vd_prescale = ext_attr->qam_vd_prescale;
		qam_vd_bit_cnt = qam_vd_prescale * fec_vd_plen;	/* temp storage */

		switch (constellation) {
		case DRX_CONSTELLATION_QAM64:
			/* a(16 bit) * b(4 bit) = 20 bit result => mult32 not needed */
			qam_vd_period =
			    qam_vd_bit_cnt * (QAM_TOP_CONSTELLATION_QAM64 + 1)
			    * (QAM_TOP_CONSTELLATION_QAM64 + 1);
			break;
		case DRX_CONSTELLATION_QAM256:
			/* a(16 bit) * b(5 bit) = 21 bit result => mult32 not needed */
			qam_vd_period =
			    qam_vd_bit_cnt * (QAM_TOP_CONSTELLATION_QAM256 + 1)
			    * (QAM_TOP_CONSTELLATION_QAM256 + 1);
			break;
		default:
			return -EINVAL;
		}
		if (qam_vd_period == 0) {
			pr_err("error: qam_vd_period is zero!\n");
			return -EIO;
		}
		qam_vd_period = fec_bits_desired / qam_vd_period;
		/* limit to max 16 bit value (I2C register width) if needed */
		if (qam_vd_period > 0xFFFF)
			qam_vd_period = 0xFFFF;

		/* a(16 bit) * b(16 bit) = 32 bit result => mult32 not needed */
		qam_vd_bit_cnt *= qam_vd_period;

		rc = drxj_dap_write_reg16(dev_addr, QAM_VD_MEASUREMENT_PERIOD__A, (u16)qam_vd_period, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, QAM_VD_MEASUREMENT_PRESCALE__A, qam_vd_prescale, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		ext_attr->qam_vd_period = (u16) qam_vd_period;
		ext_attr->qam_vd_prescale = qam_vd_prescale;
	}

	return 0;
rw_error:
	return rc;
}