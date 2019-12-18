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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; struct cxd2880_tnrdmd* diver_sub; } ;
typedef  enum cxd2880_dtv_sys { ____Placeholder_cxd2880_dtv_sys } cxd2880_dtv_sys ;

/* Variables and functions */
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 scalar_t__ CXD2880_TNRDMD_STATE_SLEEP ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_set_ts_output (struct cxd2880_tnrdmd*,int) ; 
 int x_tune3 (struct cxd2880_tnrdmd*,int,int /*<<< orphan*/ ) ; 
 int x_tune4 (struct cxd2880_tnrdmd*) ; 

int cxd2880_tnrdmd_common_tune_setting2(struct cxd2880_tnrdmd
					*tnr_dmd,
					enum cxd2880_dtv_sys sys,
					u8 en_fef_intmtnt_ctrl)
{
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	ret = x_tune3(tnr_dmd, sys, en_fef_intmtnt_ctrl);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret = x_tune3(tnr_dmd->diver_sub, sys, en_fef_intmtnt_ctrl);
		if (ret)
			return ret;
		ret = x_tune4(tnr_dmd);
		if (ret)
			return ret;
	}

	return cxd2880_tnrdmd_set_ts_output(tnr_dmd, 1);
}