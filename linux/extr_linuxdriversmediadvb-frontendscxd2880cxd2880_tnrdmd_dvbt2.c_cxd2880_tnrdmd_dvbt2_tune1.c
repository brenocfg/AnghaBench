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
typedef  int /*<<< orphan*/  u8 ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; struct cxd2880_tnrdmd* diver_sub; int /*<<< orphan*/  clk_mode; } ;
struct cxd2880_dvbt2_tune_param {scalar_t__ profile; scalar_t__ data_plp_id; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  center_freq_khz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXD2880_DTV_SYS_DVBT2 ; 
 scalar_t__ CXD2880_DVBT2_PROFILE_ANY ; 
 scalar_t__ CXD2880_DVBT2_TUNE_PARAM_PLPID_AUTO ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 scalar_t__ CXD2880_TNRDMD_STATE_SLEEP ; 
 int EINVAL ; 
 int ENOTTY ; 
 int cxd2880_tnrdmd_common_tune_setting1 (struct cxd2880_tnrdmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cxd2880_tnrdmd_dvbt2_set_plp_cfg (struct cxd2880_tnrdmd*,int,int /*<<< orphan*/ ) ; 
 int dvbt2_set_profile (struct cxd2880_tnrdmd*,scalar_t__) ; 
 int x_tune_dvbt2_demod_setting (struct cxd2880_tnrdmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cxd2880_tnrdmd_dvbt2_tune1(struct cxd2880_tnrdmd *tnr_dmd,
			       struct cxd2880_dvbt2_tune_param
			       *tune_param)
{
	int ret;

	if (!tnr_dmd || !tune_param)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN &&
	    tune_param->profile == CXD2880_DVBT2_PROFILE_ANY)
		return -ENOTTY;

	ret =
	    cxd2880_tnrdmd_common_tune_setting1(tnr_dmd, CXD2880_DTV_SYS_DVBT2,
						tune_param->center_freq_khz,
						tune_param->bandwidth, 0, 0);
	if (ret)
		return ret;

	ret =
	    x_tune_dvbt2_demod_setting(tnr_dmd, tune_param->bandwidth,
				       tnr_dmd->clk_mode);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret =
		    x_tune_dvbt2_demod_setting(tnr_dmd->diver_sub,
					       tune_param->bandwidth,
					       tnr_dmd->diver_sub->clk_mode);
		if (ret)
			return ret;
	}

	ret = dvbt2_set_profile(tnr_dmd, tune_param->profile);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret =
		    dvbt2_set_profile(tnr_dmd->diver_sub, tune_param->profile);
		if (ret)
			return ret;
	}

	if (tune_param->data_plp_id == CXD2880_DVBT2_TUNE_PARAM_PLPID_AUTO)
		ret = cxd2880_tnrdmd_dvbt2_set_plp_cfg(tnr_dmd, 1, 0);
	else
		ret =
		    cxd2880_tnrdmd_dvbt2_set_plp_cfg(tnr_dmd, 0,
					     (u8)(tune_param->data_plp_id));

	return ret;
}