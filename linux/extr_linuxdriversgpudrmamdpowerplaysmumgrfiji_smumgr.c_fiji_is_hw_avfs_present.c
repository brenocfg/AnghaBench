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
typedef  int uint32_t ;
struct pp_hwmgr {int /*<<< orphan*/  not_vf; } ;

/* Variables and functions */
 int AVFS_EN_LSB ; 
 int AVFS_EN_MSB ; 
 int /*<<< orphan*/  atomctrl_read_efuse (struct pp_hwmgr*,int,int,int,int*) ; 

__attribute__((used)) static bool fiji_is_hw_avfs_present(struct pp_hwmgr *hwmgr)
{

	uint32_t efuse = 0;
	uint32_t mask = (1 << ((AVFS_EN_MSB - AVFS_EN_LSB) + 1)) - 1;

	if (!hwmgr->not_vf)
		return false;

	if (!atomctrl_read_efuse(hwmgr, AVFS_EN_LSB, AVFS_EN_MSB,
			mask, &efuse)) {
		if (efuse)
			return true;
	}
	return false;
}