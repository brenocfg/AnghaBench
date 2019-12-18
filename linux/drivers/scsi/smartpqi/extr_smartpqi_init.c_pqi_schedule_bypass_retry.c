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
struct pqi_ctrl_info {int /*<<< orphan*/  raid_bypass_retry_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  pqi_ctrl_blocked (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pqi_schedule_bypass_retry(struct pqi_ctrl_info *ctrl_info)
{
	if (!pqi_ctrl_blocked(ctrl_info))
		schedule_work(&ctrl_info->raid_bypass_retry_work);
}