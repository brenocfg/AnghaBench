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
typedef  scalar_t__ u16 ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; scalar_t__ sys; struct cxd2880_tnrdmd* diver_sub; } ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int dvbt_calc_snr (struct cxd2880_tnrdmd*,scalar_t__,int*) ; 
 int dvbt_read_snr_reg (struct cxd2880_tnrdmd*,scalar_t__*) ; 

int cxd2880_tnrdmd_dvbt_mon_snr_diver(struct cxd2880_tnrdmd
				      *tnr_dmd, int *snr,
				      int *snr_main, int *snr_sub)
{
	u16 reg_value = 0;
	u32 reg_value_sum = 0;
	int ret;

	if (!tnr_dmd || !snr || !snr_main || !snr_sub)
		return -EINVAL;

	*snr = -1000 * 1000;
	*snr_main = -1000 * 1000;
	*snr_sub = -1000 * 1000;

	if (tnr_dmd->diver_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT)
		return -EINVAL;

	ret = dvbt_read_snr_reg(tnr_dmd, &reg_value);
	if (!ret) {
		ret = dvbt_calc_snr(tnr_dmd, reg_value, snr_main);
		if (ret)
			reg_value = 0;
	} else if (ret == -EAGAIN) {
		reg_value = 0;
	} else {
		return ret;
	}

	reg_value_sum += reg_value;

	ret = dvbt_read_snr_reg(tnr_dmd->diver_sub, &reg_value);
	if (!ret) {
		ret = dvbt_calc_snr(tnr_dmd->diver_sub, reg_value, snr_sub);
		if (ret)
			reg_value = 0;
	} else if (ret == -EAGAIN) {
		reg_value = 0;
	} else {
		return ret;
	}

	reg_value_sum += reg_value;

	return dvbt_calc_snr(tnr_dmd, reg_value_sum, snr);
}