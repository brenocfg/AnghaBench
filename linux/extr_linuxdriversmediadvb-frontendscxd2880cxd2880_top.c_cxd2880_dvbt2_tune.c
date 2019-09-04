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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; int /*<<< orphan*/  cancel; } ;
struct cxd2880_dvbt2_tune_param {scalar_t__ bandwidth; scalar_t__ profile; } ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_BW_1_7_MHZ ; 
 scalar_t__ CXD2880_DTV_BW_5_MHZ ; 
 scalar_t__ CXD2880_DTV_BW_6_MHZ ; 
 scalar_t__ CXD2880_DTV_BW_7_MHZ ; 
 scalar_t__ CXD2880_DTV_BW_8_MHZ ; 
 scalar_t__ CXD2880_DVBT2_PROFILE_BASE ; 
 scalar_t__ CXD2880_DVBT2_PROFILE_LITE ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 scalar_t__ CXD2880_TNRDMD_STATE_SLEEP ; 
 int CXD2880_TNRDMD_WAIT_AGC_STABLE ; 
 int EINVAL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cxd2880_tnrdmd_dvbt2_tune1 (struct cxd2880_tnrdmd*,struct cxd2880_dvbt2_tune_param*) ; 
 int cxd2880_tnrdmd_dvbt2_tune2 (struct cxd2880_tnrdmd*,struct cxd2880_dvbt2_tune_param*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cxd2880_dvbt2_tune(struct cxd2880_tnrdmd *tnr_dmd,
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

	atomic_set(&tnr_dmd->cancel, 0);

	if (tune_param->bandwidth != CXD2880_DTV_BW_1_7_MHZ &&
	    tune_param->bandwidth != CXD2880_DTV_BW_5_MHZ &&
	    tune_param->bandwidth != CXD2880_DTV_BW_6_MHZ &&
	    tune_param->bandwidth != CXD2880_DTV_BW_7_MHZ &&
	    tune_param->bandwidth != CXD2880_DTV_BW_8_MHZ) {
		return -ENOTTY;
	}

	if (tune_param->profile != CXD2880_DVBT2_PROFILE_BASE &&
	    tune_param->profile != CXD2880_DVBT2_PROFILE_LITE)
		return -EINVAL;

	ret = cxd2880_tnrdmd_dvbt2_tune1(tnr_dmd, tune_param);
	if (ret)
		return ret;

	usleep_range(CXD2880_TNRDMD_WAIT_AGC_STABLE * 10000,
		     CXD2880_TNRDMD_WAIT_AGC_STABLE * 10000 + 1000);

	return cxd2880_tnrdmd_dvbt2_tune2(tnr_dmd, tune_param);
}