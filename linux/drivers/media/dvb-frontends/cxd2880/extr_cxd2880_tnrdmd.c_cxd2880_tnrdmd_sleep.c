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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; int sys; void* bandwidth; struct cxd2880_tnrdmd* diver_sub; scalar_t__ frequency_khz; } ;

/* Variables and functions */
 void* CXD2880_DTV_BW_UNKNOWN ; 
#define  CXD2880_DTV_SYS_DVBT 129 
#define  CXD2880_DTV_SYS_DVBT2 128 
 void* CXD2880_DTV_SYS_UNKNOWN ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 scalar_t__ CXD2880_TNRDMD_STATE_SLEEP ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt2_sleep_setting (struct cxd2880_tnrdmd*) ; 
 int cxd2880_tnrdmd_dvbt_sleep_setting (struct cxd2880_tnrdmd*) ; 
 int cxd2880_tnrdmd_set_ts_output (struct cxd2880_tnrdmd*,int /*<<< orphan*/ ) ; 
 int x_sleep1 (struct cxd2880_tnrdmd*) ; 
 int x_sleep2 (struct cxd2880_tnrdmd*) ; 
 int x_sleep3 (struct cxd2880_tnrdmd*) ; 
 int x_sleep4 (struct cxd2880_tnrdmd*) ; 

int cxd2880_tnrdmd_sleep(struct cxd2880_tnrdmd *tnr_dmd)
{
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state == CXD2880_TNRDMD_STATE_SLEEP)
		return 0;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	ret = cxd2880_tnrdmd_set_ts_output(tnr_dmd, 0);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret = x_sleep1(tnr_dmd);
		if (ret)
			return ret;
	}

	ret = x_sleep2(tnr_dmd);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret = x_sleep2(tnr_dmd->diver_sub);
		if (ret)
			return ret;
	}

	switch (tnr_dmd->sys) {
	case CXD2880_DTV_SYS_DVBT:
		ret = cxd2880_tnrdmd_dvbt_sleep_setting(tnr_dmd);
		if (ret)
			return ret;
		break;

	case CXD2880_DTV_SYS_DVBT2:
		ret = cxd2880_tnrdmd_dvbt2_sleep_setting(tnr_dmd);
		if (ret)
			return ret;
		break;

	default:
		return -EINVAL;
	}

	ret = x_sleep3(tnr_dmd);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret = x_sleep3(tnr_dmd->diver_sub);
		if (ret)
			return ret;
	}

	ret = x_sleep4(tnr_dmd);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret = x_sleep4(tnr_dmd->diver_sub);
		if (ret)
			return ret;
	}

	tnr_dmd->state = CXD2880_TNRDMD_STATE_SLEEP;
	tnr_dmd->frequency_khz = 0;
	tnr_dmd->sys = CXD2880_DTV_SYS_UNKNOWN;
	tnr_dmd->bandwidth = CXD2880_DTV_BW_UNKNOWN;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		tnr_dmd->diver_sub->state = CXD2880_TNRDMD_STATE_SLEEP;
		tnr_dmd->diver_sub->frequency_khz = 0;
		tnr_dmd->diver_sub->sys = CXD2880_DTV_SYS_UNKNOWN;
		tnr_dmd->diver_sub->bandwidth = CXD2880_DTV_BW_UNKNOWN;
	}

	return 0;
}