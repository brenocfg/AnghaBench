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
struct i2c_device_addr {int dummy; } ;
struct drxj_data {int standard; int /*<<< orphan*/  hi_cfg_ctrl; } ;
struct drx_demod_instance {struct i2c_device_addr* my_i2c_dev_addr; scalar_t__ my_ext_attr; scalar_t__ my_common_attr; } ;
struct drx_common_attr {int current_power_mode; } ;
typedef  enum drx_power_mode { ____Placeholder_drx_power_mode } drx_power_mode ;

/* Variables and functions */
#define  DRXJ_POWER_DOWN_CORE 145 
#define  DRXJ_POWER_DOWN_MAIN_PATH 144 
#define  DRXJ_POWER_DOWN_PLL 143 
#define  DRX_POWER_DOWN 142 
#define  DRX_POWER_UP 141 
#define  DRX_STANDARD_8VSB 140 
#define  DRX_STANDARD_AUTO 139 
#define  DRX_STANDARD_FM 138 
#define  DRX_STANDARD_ITU_A 137 
#define  DRX_STANDARD_ITU_B 136 
#define  DRX_STANDARD_ITU_C 135 
#define  DRX_STANDARD_NTSC 134 
#define  DRX_STANDARD_PAL_SECAM_BG 133 
#define  DRX_STANDARD_PAL_SECAM_DK 132 
#define  DRX_STANDARD_PAL_SECAM_I 131 
#define  DRX_STANDARD_PAL_SECAM_L 130 
#define  DRX_STANDARD_PAL_SECAM_LP 129 
#define  DRX_STANDARD_UNKNOWN 128 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  SIO_CC_PWD_MODE_LEVEL_CLOCK ; 
 int /*<<< orphan*/  SIO_CC_PWD_MODE_LEVEL_NONE ; 
 int /*<<< orphan*/  SIO_CC_PWD_MODE_LEVEL_OSC ; 
 int /*<<< orphan*/  SIO_CC_PWD_MODE_LEVEL_PLL ; 
 int /*<<< orphan*/  SIO_CC_PWD_MODE__A ; 
 int /*<<< orphan*/  SIO_CC_UPDATE_KEY ; 
 int /*<<< orphan*/  SIO_CC_UPDATE__A ; 
 int /*<<< orphan*/  SIO_HI_RA_RAM_PAR_5_CFG_SLEEP_ZZZ ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drxj_reset_mode (struct drxj_data*) ; 
 int hi_cfg_command (struct drx_demod_instance*) ; 
 int init_hi (struct drx_demod_instance*) ; 
 int power_down_atv (struct drx_demod_instance*,int,int) ; 
 int power_down_qam (struct drx_demod_instance*,int) ; 
 int power_down_vsb (struct drx_demod_instance*,int) ; 
 int power_up_device (struct drx_demod_instance*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int
ctrl_power_mode(struct drx_demod_instance *demod, enum drx_power_mode *mode)
{
	struct drx_common_attr *common_attr = (struct drx_common_attr *) NULL;
	struct drxj_data *ext_attr = (struct drxj_data *) NULL;
	struct i2c_device_addr *dev_addr = (struct i2c_device_addr *)NULL;
	int rc;
	u16 sio_cc_pwd_mode = 0;

	common_attr = (struct drx_common_attr *) demod->my_common_attr;
	ext_attr = (struct drxj_data *) demod->my_ext_attr;
	dev_addr = demod->my_i2c_dev_addr;

	/* Check arguments */
	if (mode == NULL)
		return -EINVAL;

	/* If already in requested power mode, do nothing */
	if (common_attr->current_power_mode == *mode)
		return 0;

	switch (*mode) {
	case DRX_POWER_UP:
	case DRXJ_POWER_DOWN_MAIN_PATH:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_NONE;
		break;
	case DRXJ_POWER_DOWN_CORE:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_CLOCK;
		break;
	case DRXJ_POWER_DOWN_PLL:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_PLL;
		break;
	case DRX_POWER_DOWN:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_OSC;
		break;
	default:
		/* Unknow sleep mode */
		return -EINVAL;
		break;
	}

	/* Check if device needs to be powered up */
	if ((common_attr->current_power_mode != DRX_POWER_UP)) {
		rc = power_up_device(demod);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
	}

	if (*mode == DRX_POWER_UP) {
		/* Restore analog & pin configuration */

		/* Initialize default AFE configuration for VSB */
		drxj_reset_mode(ext_attr);
	} else {
		/* Power down to requested mode */
		/* Backup some register settings */
		/* Set pins with possible pull-ups connected to them in input mode */
		/* Analog power down */
		/* ADC power down */
		/* Power down device */
		/* stop all comm_exec */
		/*
		   Stop and power down previous standard
		 */

		switch (ext_attr->standard) {
		case DRX_STANDARD_ITU_A:
		case DRX_STANDARD_ITU_B:
		case DRX_STANDARD_ITU_C:
			rc = power_down_qam(demod, true);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			break;
		case DRX_STANDARD_8VSB:
			rc = power_down_vsb(demod, true);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			break;
		case DRX_STANDARD_PAL_SECAM_BG:	/* fallthrough */
		case DRX_STANDARD_PAL_SECAM_DK:	/* fallthrough */
		case DRX_STANDARD_PAL_SECAM_I:	/* fallthrough */
		case DRX_STANDARD_PAL_SECAM_L:	/* fallthrough */
		case DRX_STANDARD_PAL_SECAM_LP:	/* fallthrough */
		case DRX_STANDARD_NTSC:	/* fallthrough */
		case DRX_STANDARD_FM:
			rc = power_down_atv(demod, ext_attr->standard, true);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			break;
		case DRX_STANDARD_UNKNOWN:
			/* Do nothing */
			break;
		case DRX_STANDARD_AUTO:	/* fallthrough */
		default:
			return -EIO;
		}
		ext_attr->standard = DRX_STANDARD_UNKNOWN;
	}

	if (*mode != DRXJ_POWER_DOWN_MAIN_PATH) {
		rc = drxj_dap_write_reg16(dev_addr, SIO_CC_PWD_MODE__A, sio_cc_pwd_mode, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, SIO_CC_UPDATE__A, SIO_CC_UPDATE_KEY, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}

		if ((*mode != DRX_POWER_UP)) {
			/* Initialize HI, wakeup key especially before put IC to sleep */
			rc = init_hi(demod);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}

			ext_attr->hi_cfg_ctrl |= SIO_HI_RA_RAM_PAR_5_CFG_SLEEP_ZZZ;
			rc = hi_cfg_command(demod);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
		}
	}

	common_attr->current_power_mode = *mode;

	return 0;
rw_error:
	return rc;
}