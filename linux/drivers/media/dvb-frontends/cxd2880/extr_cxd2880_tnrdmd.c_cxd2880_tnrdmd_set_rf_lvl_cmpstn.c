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
struct cxd2880_tnrdmd {int (* rf_lvl_cmpstn ) (struct cxd2880_tnrdmd*,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 

int cxd2880_tnrdmd_set_rf_lvl_cmpstn(struct cxd2880_tnrdmd
				     *tnr_dmd,
				     int (*rf_lvl_cmpstn)
				     (struct cxd2880_tnrdmd *,
				     int *))
{
	if (!tnr_dmd)
		return -EINVAL;

	tnr_dmd->rf_lvl_cmpstn = rf_lvl_cmpstn;

	return 0;
}