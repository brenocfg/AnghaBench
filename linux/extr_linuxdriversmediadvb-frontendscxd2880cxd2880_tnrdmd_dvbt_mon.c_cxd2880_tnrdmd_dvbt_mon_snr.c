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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; scalar_t__ sys; } ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SINGLE ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt_mon_snr_diver (struct cxd2880_tnrdmd*,int*,int*,int*) ; 
 int dvbt_calc_snr (struct cxd2880_tnrdmd*,int /*<<< orphan*/ ,int*) ; 
 int dvbt_read_snr_reg (struct cxd2880_tnrdmd*,int /*<<< orphan*/ *) ; 

int cxd2880_tnrdmd_dvbt_mon_snr(struct cxd2880_tnrdmd *tnr_dmd,
				int *snr)
{
	u16 reg_value = 0;
	int ret;

	if (!tnr_dmd || !snr)
		return -EINVAL;

	*snr = -1000 * 1000;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SINGLE) {
		ret = dvbt_read_snr_reg(tnr_dmd, &reg_value);
		if (ret)
			return ret;

		ret = dvbt_calc_snr(tnr_dmd, reg_value, snr);
	} else {
		int snr_main = 0;
		int snr_sub = 0;

		ret =
		    cxd2880_tnrdmd_dvbt_mon_snr_diver(tnr_dmd, snr, &snr_main,
						      &snr_sub);
	}

	return ret;
}