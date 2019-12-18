#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct urb {int dummy; } ;
struct uas_dev_info {int /*<<< orphan*/  sense_urbs; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct uas_dev_info* hostdata; } ;

/* Variables and functions */
 struct urb* uas_alloc_sense_urb (struct uas_dev_info*,int /*<<< orphan*/ ,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  uas_log_cmd_state (struct scsi_cmnd*,char*,int) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static struct urb *uas_submit_sense_urb(struct scsi_cmnd *cmnd, gfp_t gfp)
{
	struct uas_dev_info *devinfo = cmnd->device->hostdata;
	struct urb *urb;
	int err;

	urb = uas_alloc_sense_urb(devinfo, gfp, cmnd);
	if (!urb)
		return NULL;
	usb_anchor_urb(urb, &devinfo->sense_urbs);
	err = usb_submit_urb(urb, gfp);
	if (err) {
		usb_unanchor_urb(urb);
		uas_log_cmd_state(cmnd, "sense submit err", err);
		usb_free_urb(urb);
		return NULL;
	}
	return urb;
}