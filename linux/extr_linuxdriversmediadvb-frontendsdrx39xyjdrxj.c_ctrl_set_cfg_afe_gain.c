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
struct i2c_device_addr {int dummy; } ;
struct drxj_data {int standard; int /*<<< orphan*/  qam_pga_cfg; int /*<<< orphan*/  vsb_pga_cfg; } ;
struct drxj_cfg_afe_gain {int standard; int gain; } ;
struct drx_demod_instance {scalar_t__ my_ext_attr; struct i2c_device_addr* my_i2c_dev_addr; } ;

/* Variables and functions */
#define  DRX_STANDARD_8VSB 131 
#define  DRX_STANDARD_ITU_A 130 
#define  DRX_STANDARD_ITU_B 129 
#define  DRX_STANDARD_ITU_C 128 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IQM_AF_PGA_GAIN__A ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int
ctrl_set_cfg_afe_gain(struct drx_demod_instance *demod, struct drxj_cfg_afe_gain *afe_gain)
{
	struct i2c_device_addr *dev_addr = NULL;
	struct drxj_data *ext_attr = NULL;
	int rc;
	u8 gain = 0;

	/* check arguments */
	if (afe_gain == NULL)
		return -EINVAL;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (struct drxj_data *) demod->my_ext_attr;

	switch (afe_gain->standard) {
	case DRX_STANDARD_8VSB:	/* fallthrough */
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:	/* fallthrough */
	case DRX_STANDARD_ITU_B:	/* fallthrough */
	case DRX_STANDARD_ITU_C:
#endif
		/* Do nothing */
		break;
	default:
		return -EINVAL;
	}

	/* TODO PGA gain is also written by microcode (at least by QAM and VSB)
	   So I (PJ) think interface requires choice between auto, user mode */

	if (afe_gain->gain >= 329)
		gain = 15;
	else if (afe_gain->gain <= 147)
		gain = 0;
	else
		gain = (afe_gain->gain - 140 + 6) / 13;

	/* Only if standard is currently active */
	if (ext_attr->standard == afe_gain->standard) {
			rc = drxj_dap_write_reg16(dev_addr, IQM_AF_PGA_GAIN__A, gain, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
		}

	/* Store AFE Gain settings */
	switch (afe_gain->standard) {
	case DRX_STANDARD_8VSB:
		ext_attr->vsb_pga_cfg = gain * 13 + 140;
		break;
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:	/* fallthrough */
	case DRX_STANDARD_ITU_B:	/* fallthrough */
	case DRX_STANDARD_ITU_C:
		ext_attr->qam_pga_cfg = gain * 13 + 140;
		break;
#endif
	default:
		return -EIO;
	}

	return 0;
rw_error:
	return rc;
}