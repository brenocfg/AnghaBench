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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; scalar_t__ sys; int /*<<< orphan*/  diver_sub; } ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT2 ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_mon_rf_lvl (int /*<<< orphan*/ ,int*) ; 
 int dvbt2_calc_ssi (struct cxd2880_tnrdmd*,int,int /*<<< orphan*/ *) ; 

int cxd2880_tnrdmd_dvbt2_mon_ssi_sub(struct cxd2880_tnrdmd
				     *tnr_dmd, u8 *ssi)
{
	int rf_lvl = 0;
	int ret;

	if (!tnr_dmd || !ssi)
		return -EINVAL;

	if (tnr_dmd->diver_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		return -EINVAL;

	ret = cxd2880_tnrdmd_mon_rf_lvl(tnr_dmd->diver_sub, &rf_lvl);
	if (ret)
		return ret;

	return dvbt2_calc_ssi(tnr_dmd, rf_lvl, ssi);
}