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
struct TYPE_3__ {struct bas_cardstate* bas; } ;
struct cardstate {int /*<<< orphan*/  dev; int /*<<< orphan*/  inbuf; TYPE_1__ hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  wLength; scalar_t__ wIndex; scalar_t__ wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bRequestType; } ;
struct bas_cardstate {int rcvbuf_size; int /*<<< orphan*/  timer_cmd_in; int /*<<< orphan*/  urb_cmd_in; int /*<<< orphan*/  rcvbuf; TYPE_2__ dr_cmd_in; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int BS_ATRDPEND ; 
 int BS_SUSPEND ; 
 int /*<<< orphan*/  DEBUG_USBREQ ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HD_READ_ATMESSAGE ; 
 int HZ ; 
 int /*<<< orphan*/  IN_VENDOR_REQ ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_usb_rcmsg (int) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  read_ctrl_callback ; 
 int update_basstate (struct bas_cardstate*,int,int) ; 
 int /*<<< orphan*/  usb_fill_control_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atread_submit(struct cardstate *cs, int timeout)
{
	struct bas_cardstate *ucs = cs->hw.bas;
	int basstate;
	int ret;

	gig_dbg(DEBUG_USBREQ, "-------> HD_READ_ATMESSAGE (%d)",
		ucs->rcvbuf_size);

	basstate = update_basstate(ucs, BS_ATRDPEND, 0);
	if (basstate & BS_ATRDPEND) {
		dev_err(cs->dev,
			"could not submit HD_READ_ATMESSAGE: URB busy\n");
		return -EBUSY;
	}

	if (basstate & BS_SUSPEND) {
		dev_notice(cs->dev,
			   "HD_READ_ATMESSAGE not submitted, "
			   "suspend in progress\n");
		update_basstate(ucs, 0, BS_ATRDPEND);
		/* treat like disconnect */
		return -ENODEV;
	}

	ucs->dr_cmd_in.bRequestType = IN_VENDOR_REQ;
	ucs->dr_cmd_in.bRequest = HD_READ_ATMESSAGE;
	ucs->dr_cmd_in.wValue = 0;
	ucs->dr_cmd_in.wIndex = 0;
	ucs->dr_cmd_in.wLength = cpu_to_le16(ucs->rcvbuf_size);
	usb_fill_control_urb(ucs->urb_cmd_in, ucs->udev,
			     usb_rcvctrlpipe(ucs->udev, 0),
			     (unsigned char *) &ucs->dr_cmd_in,
			     ucs->rcvbuf, ucs->rcvbuf_size,
			     read_ctrl_callback, cs->inbuf);

	ret = usb_submit_urb(ucs->urb_cmd_in, GFP_ATOMIC);
	if (ret != 0) {
		update_basstate(ucs, 0, BS_ATRDPEND);
		dev_err(cs->dev, "could not submit HD_READ_ATMESSAGE: %s\n",
			get_usb_rcmsg(ret));
		return ret;
	}

	if (timeout > 0) {
		gig_dbg(DEBUG_USBREQ, "setting timeout of %d/10 secs", timeout);
		mod_timer(&ucs->timer_cmd_in, jiffies + timeout * HZ / 10);
	}
	return 0;
}