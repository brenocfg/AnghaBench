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
struct TYPE_3__ {int /*<<< orphan*/  bchars; struct usb_device* udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_USBREQ ; 
 int /*<<< orphan*/  gigaset_dbg_buffer (int /*<<< orphan*/ ,char*,int,unsigned char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const**,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gigaset_brkchars(struct cardstate *cs, const unsigned char buf[6])
{
	struct usb_device *udev = cs->hw.usb->udev;

	gigaset_dbg_buffer(DEBUG_USBREQ, "brkchars", 6, buf);
	memcpy(cs->hw.usb->bchars, buf, 6);
	return usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0x19, 0x41,
			       0, 0, &buf, 6, 2000);
}