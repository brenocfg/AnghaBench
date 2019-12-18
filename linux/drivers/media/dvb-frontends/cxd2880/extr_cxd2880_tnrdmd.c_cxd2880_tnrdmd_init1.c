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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; struct cxd2880_tnrdmd* diver_sub; void* chip_id; int /*<<< orphan*/  cancel; scalar_t__ scan_mode; void* bandwidth; void* sys; scalar_t__ frequency_khz; void* clk_mode; void* state; } ;

/* Variables and functions */
 void* CXD2880_DTV_BW_UNKNOWN ; 
 void* CXD2880_DTV_SYS_UNKNOWN ; 
 void* CXD2880_TNRDMD_CHIP_ID_UNKNOWN ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_CHIP_ID_VALID (void*) ; 
 void* CXD2880_TNRDMD_CLOCKMODE_UNKNOWN ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 void* CXD2880_TNRDMD_STATE_UNKNOWN ; 
 int EINVAL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cxd2880_tnrdmd_chip_id (struct cxd2880_tnrdmd*,void**) ; 
 int p_init1 (struct cxd2880_tnrdmd*) ; 
 int p_init2 (struct cxd2880_tnrdmd*) ; 
 int p_init3 (struct cxd2880_tnrdmd*) ; 
 int rf_init1 (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int cxd2880_tnrdmd_init1(struct cxd2880_tnrdmd *tnr_dmd)
{
	int ret;

	if (!tnr_dmd || tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	tnr_dmd->chip_id = CXD2880_TNRDMD_CHIP_ID_UNKNOWN;
	tnr_dmd->state = CXD2880_TNRDMD_STATE_UNKNOWN;
	tnr_dmd->clk_mode = CXD2880_TNRDMD_CLOCKMODE_UNKNOWN;
	tnr_dmd->frequency_khz = 0;
	tnr_dmd->sys = CXD2880_DTV_SYS_UNKNOWN;
	tnr_dmd->bandwidth = CXD2880_DTV_BW_UNKNOWN;
	tnr_dmd->scan_mode = 0;
	atomic_set(&tnr_dmd->cancel, 0);

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		tnr_dmd->diver_sub->chip_id = CXD2880_TNRDMD_CHIP_ID_UNKNOWN;
		tnr_dmd->diver_sub->state = CXD2880_TNRDMD_STATE_UNKNOWN;
		tnr_dmd->diver_sub->clk_mode = CXD2880_TNRDMD_CLOCKMODE_UNKNOWN;
		tnr_dmd->diver_sub->frequency_khz = 0;
		tnr_dmd->diver_sub->sys = CXD2880_DTV_SYS_UNKNOWN;
		tnr_dmd->diver_sub->bandwidth = CXD2880_DTV_BW_UNKNOWN;
		tnr_dmd->diver_sub->scan_mode = 0;
		atomic_set(&tnr_dmd->diver_sub->cancel, 0);
	}

	ret = cxd2880_tnrdmd_chip_id(tnr_dmd, &tnr_dmd->chip_id);
	if (ret)
		return ret;

	if (!CXD2880_TNRDMD_CHIP_ID_VALID(tnr_dmd->chip_id))
		return -ENOTTY;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret =
		    cxd2880_tnrdmd_chip_id(tnr_dmd->diver_sub,
					   &tnr_dmd->diver_sub->chip_id);
		if (ret)
			return ret;

		if (!CXD2880_TNRDMD_CHIP_ID_VALID(tnr_dmd->diver_sub->chip_id))
			return -ENOTTY;
	}

	ret = p_init1(tnr_dmd);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret = p_init1(tnr_dmd->diver_sub);
		if (ret)
			return ret;
	}

	usleep_range(1000, 2000);

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret = p_init2(tnr_dmd->diver_sub);
		if (ret)
			return ret;
	}

	ret = p_init2(tnr_dmd);
	if (ret)
		return ret;

	usleep_range(5000, 6000);

	ret = p_init3(tnr_dmd);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN) {
		ret = p_init3(tnr_dmd->diver_sub);
		if (ret)
			return ret;
	}

	ret = rf_init1(tnr_dmd);
	if (ret)
		return ret;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
		ret = rf_init1(tnr_dmd->diver_sub);

	return ret;
}