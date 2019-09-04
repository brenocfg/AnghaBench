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
struct usb_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* usb; } ;
struct cardstate {TYPE_2__ hw; } ;
struct TYPE_3__ {struct usb_device* udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_USBREQ ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 unsigned int tiocm_to_gigaset (unsigned int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gigaset_set_modem_ctrl(struct cardstate *cs, unsigned old_state,
				  unsigned new_state)
{
	struct usb_device *udev = cs->hw.usb->udev;
	unsigned mask, val;
	int r;

	mask = tiocm_to_gigaset(old_state ^ new_state);
	val = tiocm_to_gigaset(new_state);

	gig_dbg(DEBUG_USBREQ, "set flags 0x%02x with mask 0x%02x", val, mask);
	r = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 7, 0x41,
			    (val & 0xff) | ((mask & 0xff) << 8), 0,
			    NULL, 0, 2000 /* timeout? */);
	if (r < 0)
		return r;
	return 0;
}