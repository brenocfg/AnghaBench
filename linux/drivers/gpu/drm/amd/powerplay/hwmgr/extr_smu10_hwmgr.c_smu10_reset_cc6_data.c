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
struct smu10_hwmgr {int cc6_disable; int pstate_disable; int cc6_setting_changed; scalar_t__ separation_time; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */

__attribute__((used)) static int smu10_reset_cc6_data(struct pp_hwmgr *hwmgr)
{
	struct smu10_hwmgr *smu10_data = (struct smu10_hwmgr *)(hwmgr->backend);

	smu10_data->separation_time = 0;
	smu10_data->cc6_disable = false;
	smu10_data->pstate_disable = false;
	smu10_data->cc6_setting_changed = false;

	return 0;
}