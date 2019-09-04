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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; int /*<<< orphan*/  diver_sub; } ;

/* Variables and functions */
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt2_mon_carrier_offset (int /*<<< orphan*/ ,int*) ; 

int cxd2880_tnrdmd_dvbt2_mon_carrier_offset_sub(struct
						cxd2880_tnrdmd
						*tnr_dmd,
						int *offset)
{
	if (!tnr_dmd || !offset)
		return -EINVAL;

	if (tnr_dmd->diver_mode != CXD2880_TNRDMD_DIVERMODE_MAIN)
		return -EINVAL;

	return cxd2880_tnrdmd_dvbt2_mon_carrier_offset(tnr_dmd->diver_sub,
						       offset);
}