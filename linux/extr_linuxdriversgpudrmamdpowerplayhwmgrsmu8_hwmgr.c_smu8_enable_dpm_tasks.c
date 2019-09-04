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
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  smu8_program_bootup_state (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_program_voting_clients (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_reset_acp_boot_level (struct pp_hwmgr*) ; 
 scalar_t__ smu8_start_dpm (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu8_enable_dpm_tasks(struct pp_hwmgr *hwmgr)
{
	smu8_program_voting_clients(hwmgr);
	if (smu8_start_dpm(hwmgr))
		return -EINVAL;
	smu8_program_bootup_state(hwmgr);
	smu8_reset_acp_boot_level(hwmgr);

	return 0;
}