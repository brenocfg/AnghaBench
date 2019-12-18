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
struct drxj_data {int standard; } ;
struct drx_demod_instance {int /*<<< orphan*/  my_i2c_dev_addr; scalar_t__ my_ext_attr; } ;
typedef  enum drx_standard { ____Placeholder_drx_standard } drx_standard ;

/* Variables and functions */
#define  DRX_STANDARD_8VSB 133 
#define  DRX_STANDARD_AUTO 132 
#define  DRX_STANDARD_ITU_A 131 
#define  DRX_STANDARD_ITU_B 130 
#define  DRX_STANDARD_ITU_C 129 
#define  DRX_STANDARD_UNKNOWN 128 
 int EINVAL ; 
 int /*<<< orphan*/  SCU_RAM_VERSION_HI__A ; 
 int drxj_dap_read_reg16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int power_down_qam (struct drx_demod_instance*,int) ; 
 int power_down_vsb (struct drx_demod_instance*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int set_vsb_leak_n_gain (struct drx_demod_instance*) ; 

__attribute__((used)) static int
ctrl_set_standard(struct drx_demod_instance *demod, enum drx_standard *standard)
{
	struct drxj_data *ext_attr = NULL;
	int rc;
	enum drx_standard prev_standard;

	/* check arguments */
	if ((standard == NULL) || (demod == NULL))
		return -EINVAL;

	ext_attr = (struct drxj_data *) demod->my_ext_attr;
	prev_standard = ext_attr->standard;

	/*
	   Stop and power down previous standard
	 */
	switch (prev_standard) {
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:	/* fallthrough */
	case DRX_STANDARD_ITU_B:	/* fallthrough */
	case DRX_STANDARD_ITU_C:
		rc = power_down_qam(demod, false);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
#endif
	case DRX_STANDARD_8VSB:
		rc = power_down_vsb(demod, false);
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
		return -EINVAL;
	}

	/*
	   Initialize channel independent registers
	   Power up new standard
	 */
	ext_attr->standard = *standard;

	switch (*standard) {
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:	/* fallthrough */
	case DRX_STANDARD_ITU_B:	/* fallthrough */
	case DRX_STANDARD_ITU_C:
		do {
			u16 dummy;
			rc = drxj_dap_read_reg16(demod->my_i2c_dev_addr, SCU_RAM_VERSION_HI__A, &dummy, 0);
			if (rc != 0) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
		} while (0);
		break;
#endif
	case DRX_STANDARD_8VSB:
		rc = set_vsb_leak_n_gain(demod);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		break;
	default:
		ext_attr->standard = DRX_STANDARD_UNKNOWN;
		return -EINVAL;
		break;
	}

	return 0;
rw_error:
	/* Don't know what the standard is now ... try again */
	ext_attr->standard = DRX_STANDARD_UNKNOWN;
	return rc;
}