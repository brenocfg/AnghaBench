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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ UFS_UPIU_MAX_GENERAL_LUN ; 
 scalar_t__ UFS_UPIU_RPMB_WLUN ; 

__attribute__((used)) static inline bool ufs_is_valid_unit_desc_lun(u8 lun)
{
	return lun == UFS_UPIU_RPMB_WLUN || (lun < UFS_UPIU_MAX_GENERAL_LUN);
}