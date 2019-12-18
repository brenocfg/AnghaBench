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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; } ;
typedef  enum cxd2880_tnrdmd_lock_result { ____Placeholder_cxd2880_tnrdmd_lock_result } cxd2880_tnrdmd_lock_result ;

/* Variables and functions */
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SINGLE ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 int CXD2880_TNRDMD_LOCK_RESULT_LOCKED ; 
 int CXD2880_TNRDMD_LOCK_RESULT_NOTDETECT ; 
 int CXD2880_TNRDMD_LOCK_RESULT_UNLOCKED ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt_mon_sync_stat (struct cxd2880_tnrdmd*,int*,int*,int*) ; 
 int cxd2880_tnrdmd_dvbt_mon_sync_stat_sub (struct cxd2880_tnrdmd*,int*,int*) ; 

int cxd2880_tnrdmd_dvbt_check_demod_lock(struct cxd2880_tnrdmd
					 *tnr_dmd,
					 enum
					 cxd2880_tnrdmd_lock_result
					 *lock)
{
	int ret;

	u8 sync_stat = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	u8 unlock_detected_sub = 0;

	if (!tnr_dmd || !lock)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	ret =
	    cxd2880_tnrdmd_dvbt_mon_sync_stat(tnr_dmd, &sync_stat, &ts_lock,
					      &unlock_detected);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SINGLE) {
		if (sync_stat == 6)
			*lock = CXD2880_TNRDMD_LOCK_RESULT_LOCKED;
		else if (unlock_detected)
			*lock = CXD2880_TNRDMD_LOCK_RESULT_UNLOCKED;
		else
			*lock = CXD2880_TNRDMD_LOCK_RESULT_NOTDETECT;

		return ret;
	}

	if (sync_stat == 6) {
		*lock = CXD2880_TNRDMD_LOCK_RESULT_LOCKED;
		return ret;
	}

	ret =
	    cxd2880_tnrdmd_dvbt_mon_sync_stat_sub(tnr_dmd, &sync_stat,
						  &unlock_detected_sub);
	if (ret)
		return ret;

	if (sync_stat == 6)
		*lock = CXD2880_TNRDMD_LOCK_RESULT_LOCKED;
	else if (unlock_detected && unlock_detected_sub)
		*lock = CXD2880_TNRDMD_LOCK_RESULT_UNLOCKED;
	else
		*lock = CXD2880_TNRDMD_LOCK_RESULT_NOTDETECT;

	return ret;
}