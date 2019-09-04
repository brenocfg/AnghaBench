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
typedef  scalar_t__ uint32_t ;
struct smu7_hwmgr {int /*<<< orphan*/  is_memory_gddr5; } ;
struct pp_hwmgr {int chip_id; scalar_t__ backend; } ;

/* Variables and functions */
#define  CHIP_POLARIS10 131 
#define  CHIP_POLARIS11 130 
#define  CHIP_POLARIS12 129 
#define  CHIP_VEGAM 128 

__attribute__((used)) static int smu7_vblank_too_short(struct pp_hwmgr *hwmgr,
				 uint32_t vblank_time_us)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	uint32_t switch_limit_us;

	switch (hwmgr->chip_id) {
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
		switch_limit_us = data->is_memory_gddr5 ? 190 : 150;
		break;
	case CHIP_VEGAM:
		switch_limit_us = 30;
		break;
	default:
		switch_limit_us = data->is_memory_gddr5 ? 450 : 150;
		break;
	}

	if (vblank_time_us < switch_limit_us)
		return true;
	else
		return false;
}