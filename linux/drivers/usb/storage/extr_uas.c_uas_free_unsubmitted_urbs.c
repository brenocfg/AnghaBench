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
struct uas_cmd_info {int state; int /*<<< orphan*/  data_out_urb; int /*<<< orphan*/  data_in_urb; int /*<<< orphan*/  cmd_urb; } ;
struct scsi_cmnd {int /*<<< orphan*/  SCp; } ;

/* Variables and functions */
 int DATA_IN_URB_INFLIGHT ; 
 int DATA_OUT_URB_INFLIGHT ; 
 int SUBMIT_CMD_URB ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uas_free_unsubmitted_urbs(struct scsi_cmnd *cmnd)
{
	struct uas_cmd_info *cmdinfo;

	if (!cmnd)
		return;

	cmdinfo = (void *)&cmnd->SCp;

	if (cmdinfo->state & SUBMIT_CMD_URB)
		usb_free_urb(cmdinfo->cmd_urb);

	/* data urbs may have never gotten their submit flag set */
	if (!(cmdinfo->state & DATA_IN_URB_INFLIGHT))
		usb_free_urb(cmdinfo->data_in_urb);
	if (!(cmdinfo->state & DATA_OUT_URB_INFLIGHT))
		usb_free_urb(cmdinfo->data_out_urb);
}