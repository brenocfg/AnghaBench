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
 int /*<<< orphan*/  smu8_clear_voting_clients (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_disable_nb_dpm (struct pp_hwmgr*) ; 
 scalar_t__ smu8_stop_dpm (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu8_disable_dpm_tasks(struct pp_hwmgr *hwmgr)
{
	smu8_disable_nb_dpm(hwmgr);

	smu8_clear_voting_clients(hwmgr);
	if (smu8_stop_dpm(hwmgr))
		return -EINVAL;

	return 0;
}