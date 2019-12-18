#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct megasas_instance {TYPE_1__* instancet; } ;
struct megasas_header {int cmd_status; } ;
struct megasas_cmd {TYPE_2__* frame; } ;
struct TYPE_4__ {struct megasas_header hdr; } ;
struct TYPE_3__ {int (* read_fw_status_reg ) (struct megasas_instance*) ;} ;

/* Variables and functions */
 int DCMD_FAILED ; 
 int DCMD_SUCCESS ; 
 int DCMD_TIMEOUT ; 
 int MFI_STATE_FAULT ; 
 int MFI_STATE_MASK ; 
 int MFI_STAT_INVALID_STATUS ; 
 int MFI_STAT_OK ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rmb () ; 
 int stub1 (struct megasas_instance*) ; 

int
wait_and_poll(struct megasas_instance *instance, struct megasas_cmd *cmd,
	int seconds)
{
	int i;
	struct megasas_header *frame_hdr = &cmd->frame->hdr;
	u32 status_reg;

	u32 msecs = seconds * 1000;

	/*
	 * Wait for cmd_status to change
	 */
	for (i = 0; (i < msecs) && (frame_hdr->cmd_status == 0xff); i += 20) {
		rmb();
		msleep(20);
		if (!(i % 5000)) {
			status_reg = instance->instancet->read_fw_status_reg(instance)
					& MFI_STATE_MASK;
			if (status_reg == MFI_STATE_FAULT)
				break;
		}
	}

	if (frame_hdr->cmd_status == MFI_STAT_INVALID_STATUS)
		return DCMD_TIMEOUT;
	else if (frame_hdr->cmd_status == MFI_STAT_OK)
		return DCMD_SUCCESS;
	else
		return DCMD_FAILED;
}