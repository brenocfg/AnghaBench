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
struct cardstate {int /*<<< orphan*/  dev; TYPE_1__ hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  wLength; scalar_t__ wIndex; scalar_t__ wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bRequestType; } ;
struct bas_cardstate {int /*<<< orphan*/  timer_atrdy; int /*<<< orphan*/  urb_cmd_out; TYPE_2__ dr_cmd_out; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ATRDY_TIMEOUT ; 
 int BS_ATREADY ; 
 int BS_ATTIMER ; 
 int BS_ATWRPEND ; 
 int /*<<< orphan*/  DEBUG_OUTPUT ; 
 int /*<<< orphan*/  DEBUG_USBREQ ; 
 int EBUSY ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HD_WRITE_ATMESSAGE ; 
 int HZ ; 
 int /*<<< orphan*/  OUT_VENDOR_REQ ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_usb_rcmsg (int) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int update_basstate (struct bas_cardstate*,int,int) ; 
 int /*<<< orphan*/  usb_fill_control_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,struct cardstate*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_command_callback ; 

__attribute__((used)) static int atwrite_submit(struct cardstate *cs, unsigned char *buf, int len)
{
	struct bas_cardstate *ucs = cs->hw.bas;
	int rc;

	gig_dbg(DEBUG_USBREQ, "-------> HD_WRITE_ATMESSAGE (%d)", len);

	if (update_basstate(ucs, BS_ATWRPEND, 0) & BS_ATWRPEND) {
		dev_err(cs->dev,
			"could not submit HD_WRITE_ATMESSAGE: URB busy\n");
		return -EBUSY;
	}

	ucs->dr_cmd_out.bRequestType = OUT_VENDOR_REQ;
	ucs->dr_cmd_out.bRequest = HD_WRITE_ATMESSAGE;
	ucs->dr_cmd_out.wValue = 0;
	ucs->dr_cmd_out.wIndex = 0;
	ucs->dr_cmd_out.wLength = cpu_to_le16(len);
	usb_fill_control_urb(ucs->urb_cmd_out, ucs->udev,
			     usb_sndctrlpipe(ucs->udev, 0),
			     (unsigned char *) &ucs->dr_cmd_out, buf, len,
			     write_command_callback, cs);
	rc = usb_submit_urb(ucs->urb_cmd_out, GFP_ATOMIC);
	if (unlikely(rc)) {
		update_basstate(ucs, 0, BS_ATWRPEND);
		dev_err(cs->dev, "could not submit HD_WRITE_ATMESSAGE: %s\n",
			get_usb_rcmsg(rc));
		return rc;
	}

	/* submitted successfully, start timeout if necessary */
	if (!(update_basstate(ucs, BS_ATTIMER, BS_ATREADY) & BS_ATTIMER)) {
		gig_dbg(DEBUG_OUTPUT, "setting ATREADY timeout of %d/10 secs",
			ATRDY_TIMEOUT);
		mod_timer(&ucs->timer_atrdy, jiffies + ATRDY_TIMEOUT * HZ / 10);
	}
	return 0;
}