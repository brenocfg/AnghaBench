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
struct bmic_identify_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMIC_IDENTIFY_CONTROLLER ; 
 int pqi_send_ctrl_raid_request (struct pqi_ctrl_info*,int /*<<< orphan*/ ,struct bmic_identify_controller*,int) ; 

__attribute__((used)) static inline int pqi_identify_controller(struct pqi_ctrl_info *ctrl_info,
		struct bmic_identify_controller *buffer)
{
	return pqi_send_ctrl_raid_request(ctrl_info, BMIC_IDENTIFY_CONTROLLER,
			buffer, sizeof(*buffer));
}