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
typedef  int /*<<< orphan*/  u16 ;
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INQUIRY ; 
 int /*<<< orphan*/  NO_TIMEOUT ; 
 int pqi_send_scsi_raid_request (struct pqi_ctrl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pqi_scsi_inquiry(struct pqi_ctrl_info *ctrl_info,
	u8 *scsi3addr, u16 vpd_page, void *buffer, size_t buffer_length)
{
	return pqi_send_scsi_raid_request(ctrl_info, INQUIRY, scsi3addr,
		buffer, buffer_length, vpd_page, NULL, NO_TIMEOUT);
}