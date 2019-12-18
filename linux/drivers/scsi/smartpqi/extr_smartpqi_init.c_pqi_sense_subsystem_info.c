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
struct pqi_ctrl_info {int dummy; } ;
struct bmic_sense_subsystem_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMIC_SENSE_SUBSYSTEM_INFORMATION ; 
 int pqi_send_ctrl_raid_request (struct pqi_ctrl_info*,int /*<<< orphan*/ ,struct bmic_sense_subsystem_info*,int) ; 

__attribute__((used)) static inline int pqi_sense_subsystem_info(struct  pqi_ctrl_info *ctrl_info,
		struct bmic_sense_subsystem_info *sense_info)
{
	return pqi_send_ctrl_raid_request(ctrl_info,
			BMIC_SENSE_SUBSYSTEM_INFORMATION,
			sense_info, sizeof(*sense_info));
}