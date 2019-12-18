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
struct uwb_rc {int dummy; } ;
struct usb_interface {int dummy; } ;
struct hwarc {struct uwb_rc* uwb_rc; } ;

/* Variables and functions */
 struct hwarc* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  uwb_rc_pre_reset (struct uwb_rc*) ; 

__attribute__((used)) static int hwarc_pre_reset(struct usb_interface *iface)
{
	struct hwarc *hwarc = usb_get_intfdata(iface);
	struct uwb_rc *uwb_rc = hwarc->uwb_rc;

	uwb_rc_pre_reset(uwb_rc);
	return 0;
}