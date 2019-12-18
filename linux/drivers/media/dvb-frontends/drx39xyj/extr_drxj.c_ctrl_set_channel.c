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
typedef  scalar_t__ u32 ;
struct i2c_device_addr {int dummy; } ;
struct drxuio_data {int member_1; int value; int /*<<< orphan*/  member_0; } ;
struct drxuio_cfg {scalar_t__ member_1; int /*<<< orphan*/  member_0; } ;
struct drxj_data {int standard; scalar_t__ uio_sma_tx_mode; int reset_pkt_err_acc; int /*<<< orphan*/  mirror; } ;
struct drx_demod_instance {scalar_t__ my_ext_attr; struct i2c_device_addr* my_i2c_dev_addr; } ;
struct drx_channel {int bandwidth; scalar_t__ symbolrate; int constellation; int interleavemode; int /*<<< orphan*/  mirror; } ;
typedef  scalar_t__ s32 ;
typedef  enum drx_standard { ____Placeholder_drx_standard } drx_standard ;

/* Variables and functions */
 scalar_t__ DRXJ_QAM_SYMBOLRATE_MAX ; 
 scalar_t__ DRXJ_QAM_SYMBOLRATE_MIN ; 
#define  DRX_BANDWIDTH_6MHZ 161 
#define  DRX_BANDWIDTH_7MHZ 160 
#define  DRX_BANDWIDTH_8MHZ 159 
#define  DRX_BANDWIDTH_UNKNOWN 158 
#define  DRX_CONSTELLATION_AUTO 157 
#define  DRX_CONSTELLATION_QAM128 156 
#define  DRX_CONSTELLATION_QAM16 155 
#define  DRX_CONSTELLATION_QAM256 154 
#define  DRX_CONSTELLATION_QAM32 153 
#define  DRX_CONSTELLATION_QAM64 152 
#define  DRX_INTERLEAVEMODE_AUTO 151 
#define  DRX_INTERLEAVEMODE_B52_M240 150 
#define  DRX_INTERLEAVEMODE_B52_M720 149 
#define  DRX_INTERLEAVEMODE_I128_J1 148 
#define  DRX_INTERLEAVEMODE_I128_J1_V2 147 
#define  DRX_INTERLEAVEMODE_I128_J2 146 
#define  DRX_INTERLEAVEMODE_I128_J3 145 
#define  DRX_INTERLEAVEMODE_I128_J4 144 
#define  DRX_INTERLEAVEMODE_I128_J5 143 
#define  DRX_INTERLEAVEMODE_I128_J6 142 
#define  DRX_INTERLEAVEMODE_I128_J7 141 
#define  DRX_INTERLEAVEMODE_I128_J8 140 
#define  DRX_INTERLEAVEMODE_I12_J17 139 
#define  DRX_INTERLEAVEMODE_I16_J8 138 
#define  DRX_INTERLEAVEMODE_I32_J4 137 
#define  DRX_INTERLEAVEMODE_I5_J4 136 
#define  DRX_INTERLEAVEMODE_I64_J2 135 
#define  DRX_INTERLEAVEMODE_I8_J16 134 
#define  DRX_INTERLEAVEMODE_UNKNOWN 133 
 int /*<<< orphan*/  DRX_MIRROR_AUTO ; 
 int /*<<< orphan*/  DRX_MIRROR_NO ; 
#define  DRX_STANDARD_8VSB 132 
#define  DRX_STANDARD_ITU_A 131 
#define  DRX_STANDARD_ITU_B 130 
#define  DRX_STANDARD_ITU_C 129 
 int DRX_STANDARD_NTSC ; 
#define  DRX_STANDARD_UNKNOWN 128 
 int /*<<< orphan*/  DRX_UIO1 ; 
 scalar_t__ DRX_UIO_MODE_FIRMWARE_SAW ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  SCU_COMM_EXEC_ACTIVE ; 
 int /*<<< orphan*/  SCU_COMM_EXEC__A ; 
 int ctrl_set_uio_cfg (struct drx_demod_instance*,struct drxuio_cfg*) ; 
 int ctrl_uio_write (struct drx_demod_instance*,struct drxuio_data*) ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int set_frequency (struct drx_demod_instance*,struct drx_channel*,scalar_t__) ; 
 int set_qam_channel (struct drx_demod_instance*,struct drx_channel*,scalar_t__) ; 
 int set_vsb (struct drx_demod_instance*) ; 

__attribute__((used)) static int
ctrl_set_channel(struct drx_demod_instance *demod, struct drx_channel *channel)
{
	int rc;
	s32 tuner_freq_offset = 0;
	struct drxj_data *ext_attr = NULL;
	struct i2c_device_addr *dev_addr = NULL;
	enum drx_standard standard = DRX_STANDARD_UNKNOWN;
#ifndef DRXJ_VSB_ONLY
	u32 min_symbol_rate = 0;
	u32 max_symbol_rate = 0;
	int bandwidth_temp = 0;
	int bandwidth = 0;
#endif
   /*== check arguments ======================================================*/
	if ((demod == NULL) || (channel == NULL))
		return -EINVAL;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (struct drxj_data *) demod->my_ext_attr;
	standard = ext_attr->standard;

	/* check valid standards */
	switch (standard) {
	case DRX_STANDARD_8VSB:
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:
	case DRX_STANDARD_ITU_B:
	case DRX_STANDARD_ITU_C:
#endif /* DRXJ_VSB_ONLY */
		break;
	case DRX_STANDARD_UNKNOWN:
	default:
		return -EINVAL;
	}

	/* check bandwidth QAM annex B, NTSC and 8VSB */
	if ((standard == DRX_STANDARD_ITU_B) ||
	    (standard == DRX_STANDARD_8VSB) ||
	    (standard == DRX_STANDARD_NTSC)) {
		switch (channel->bandwidth) {
		case DRX_BANDWIDTH_6MHZ:
		case DRX_BANDWIDTH_UNKNOWN:	/* fall through */
			channel->bandwidth = DRX_BANDWIDTH_6MHZ;
			break;
		case DRX_BANDWIDTH_8MHZ:	/* fall through */
		case DRX_BANDWIDTH_7MHZ:	/* fall through */
		default:
			return -EINVAL;
		}
	}

	/* For QAM annex A and annex C:
	   -check symbolrate and constellation
	   -derive bandwidth from symbolrate (input bandwidth is ignored)
	 */
#ifndef DRXJ_VSB_ONLY
	if ((standard == DRX_STANDARD_ITU_A) ||
	    (standard == DRX_STANDARD_ITU_C)) {
		struct drxuio_cfg uio_cfg = { DRX_UIO1, DRX_UIO_MODE_FIRMWARE_SAW };
		int bw_rolloff_factor = 0;

		bw_rolloff_factor = (standard == DRX_STANDARD_ITU_A) ? 115 : 113;
		min_symbol_rate = DRXJ_QAM_SYMBOLRATE_MIN;
		max_symbol_rate = DRXJ_QAM_SYMBOLRATE_MAX;
		/* config SMA_TX pin to SAW switch mode */
		rc = ctrl_set_uio_cfg(demod, &uio_cfg);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}

		if (channel->symbolrate < min_symbol_rate ||
		    channel->symbolrate > max_symbol_rate) {
			return -EINVAL;
		}

		switch (channel->constellation) {
		case DRX_CONSTELLATION_QAM16:	/* fall through */
		case DRX_CONSTELLATION_QAM32:	/* fall through */
		case DRX_CONSTELLATION_QAM64:	/* fall through */
		case DRX_CONSTELLATION_QAM128:	/* fall through */
		case DRX_CONSTELLATION_QAM256:
			bandwidth_temp = channel->symbolrate * bw_rolloff_factor;
			bandwidth = bandwidth_temp / 100;

			if ((bandwidth_temp % 100) >= 50)
				bandwidth++;

			if (bandwidth <= 6100000) {
				channel->bandwidth = DRX_BANDWIDTH_6MHZ;
			} else if ((bandwidth > 6100000)
				   && (bandwidth <= 7100000)) {
				channel->bandwidth = DRX_BANDWIDTH_7MHZ;
			} else if (bandwidth > 7100000) {
				channel->bandwidth = DRX_BANDWIDTH_8MHZ;
			}
			break;
		default:
			return -EINVAL;
		}
	}

	/* For QAM annex B:
	   -check constellation
	 */
	if (standard == DRX_STANDARD_ITU_B) {
		switch (channel->constellation) {
		case DRX_CONSTELLATION_AUTO:
		case DRX_CONSTELLATION_QAM256:
		case DRX_CONSTELLATION_QAM64:
			break;
		default:
			return -EINVAL;
		}

		switch (channel->interleavemode) {
		case DRX_INTERLEAVEMODE_I128_J1:
		case DRX_INTERLEAVEMODE_I128_J1_V2:
		case DRX_INTERLEAVEMODE_I128_J2:
		case DRX_INTERLEAVEMODE_I64_J2:
		case DRX_INTERLEAVEMODE_I128_J3:
		case DRX_INTERLEAVEMODE_I32_J4:
		case DRX_INTERLEAVEMODE_I128_J4:
		case DRX_INTERLEAVEMODE_I16_J8:
		case DRX_INTERLEAVEMODE_I128_J5:
		case DRX_INTERLEAVEMODE_I8_J16:
		case DRX_INTERLEAVEMODE_I128_J6:
		case DRX_INTERLEAVEMODE_I128_J7:
		case DRX_INTERLEAVEMODE_I128_J8:
		case DRX_INTERLEAVEMODE_I12_J17:
		case DRX_INTERLEAVEMODE_I5_J4:
		case DRX_INTERLEAVEMODE_B52_M240:
		case DRX_INTERLEAVEMODE_B52_M720:
		case DRX_INTERLEAVEMODE_UNKNOWN:
		case DRX_INTERLEAVEMODE_AUTO:
			break;
		default:
			return -EINVAL;
		}
	}

	if ((ext_attr->uio_sma_tx_mode) == DRX_UIO_MODE_FIRMWARE_SAW) {
		/* SAW SW, user UIO is used for switchable SAW */
		struct drxuio_data uio1 = { DRX_UIO1, false };

		switch (channel->bandwidth) {
		case DRX_BANDWIDTH_8MHZ:
			uio1.value = true;
			break;
		case DRX_BANDWIDTH_7MHZ:
			uio1.value = false;
			break;
		case DRX_BANDWIDTH_6MHZ:
			uio1.value = false;
			break;
		case DRX_BANDWIDTH_UNKNOWN:
		default:
			return -EINVAL;
		}

		rc = ctrl_uio_write(demod, &uio1);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
	}
#endif /* DRXJ_VSB_ONLY */
	rc = drxj_dap_write_reg16(dev_addr, SCU_COMM_EXEC__A, SCU_COMM_EXEC_ACTIVE, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	tuner_freq_offset = 0;

   /*== Setup demod for specific standard ====================================*/
	switch (standard) {
	case DRX_STANDARD_8VSB:
		if (channel->mirror == DRX_MIRROR_AUTO)
			ext_attr->mirror = DRX_MIRROR_NO;
		else
			ext_attr->mirror = channel->mirror;
		rc = set_vsb(demod);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = set_frequency(demod, channel, tuner_freq_offset);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:	/* fallthrough */
	case DRX_STANDARD_ITU_B:	/* fallthrough */
	case DRX_STANDARD_ITU_C:
		rc = set_qam_channel(demod, channel, tuner_freq_offset);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
#endif
	case DRX_STANDARD_UNKNOWN:
	default:
		return -EIO;
	}

	/* flag the packet error counter reset */
	ext_attr->reset_pkt_err_acc = true;

	return 0;
rw_error:
	return rc;
}