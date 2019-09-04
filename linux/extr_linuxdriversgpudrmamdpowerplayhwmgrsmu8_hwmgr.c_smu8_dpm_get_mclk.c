#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  bootup_uma_clock; } ;
struct smu8_hwmgr {TYPE_1__ sys_info; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t smu8_dpm_get_mclk(struct pp_hwmgr *hwmgr, bool low)
{
	struct smu8_hwmgr *data = hwmgr->backend;

	return data->sys_info.bootup_uma_clock;
}