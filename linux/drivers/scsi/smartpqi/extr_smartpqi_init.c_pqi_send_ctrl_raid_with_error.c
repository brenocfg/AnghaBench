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
typedef  int /*<<< orphan*/  u8 ;
struct pqi_raid_error_info {int dummy; } ;
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_TIMEOUT ; 
 int /*<<< orphan*/  RAID_CTLR_LUNID ; 
 int pqi_send_scsi_raid_request (struct pqi_ctrl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,struct pqi_raid_error_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pqi_send_ctrl_raid_with_error(struct pqi_ctrl_info *ctrl_info,
		u8 cmd, void *buffer, size_t buffer_length,
		struct pqi_raid_error_info *error_info)
{
	return pqi_send_scsi_raid_request(ctrl_info, cmd, RAID_CTLR_LUNID,
			buffer, buffer_length, 0, error_info, NO_TIMEOUT);
}