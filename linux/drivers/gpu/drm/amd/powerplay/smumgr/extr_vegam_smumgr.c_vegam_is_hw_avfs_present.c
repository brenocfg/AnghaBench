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
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ixSMU_EFUSE_0 ; 

__attribute__((used)) static bool vegam_is_hw_avfs_present(struct pp_hwmgr *hwmgr)
{
	uint32_t efuse;

	efuse = cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC,
			ixSMU_EFUSE_0 + (49 * 4));
	efuse &= 0x00000001;

	if (efuse)
		return true;

	return false;
}