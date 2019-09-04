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
struct cxd2880_tnrdmd_lna_thrs_tbl_cable {int dummy; } ;
struct cxd2880_tnrdmd_lna_thrs_tbl_air {int dummy; } ;
struct cxd2880_tnrdmd {struct cxd2880_tnrdmd_lna_thrs_tbl_cable* lna_thrs_tbl_cable; struct cxd2880_tnrdmd_lna_thrs_tbl_air* lna_thrs_tbl_air; } ;

/* Variables and functions */
 int EINVAL ; 

int cxd2880_tnrdmd_set_lna_thrs(struct cxd2880_tnrdmd *tnr_dmd,
				struct cxd2880_tnrdmd_lna_thrs_tbl_air
				*tbl_air,
				struct cxd2880_tnrdmd_lna_thrs_tbl_cable
				*tbl_cable)
{
	if (!tnr_dmd)
		return -EINVAL;

	tnr_dmd->lna_thrs_tbl_air = tbl_air;
	tnr_dmd->lna_thrs_tbl_cable = tbl_cable;

	return 0;
}