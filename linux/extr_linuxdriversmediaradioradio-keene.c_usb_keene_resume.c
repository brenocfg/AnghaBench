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
struct usb_interface {int dummy; } ;
struct keene_device {int /*<<< orphan*/  curfreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  keene_cmd_main (struct keene_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  keene_cmd_set (struct keene_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct keene_device* to_keene_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int usb_keene_resume(struct usb_interface *intf)
{
	struct keene_device *radio = to_keene_dev(usb_get_intfdata(intf));

	mdelay(50);
	keene_cmd_set(radio);
	keene_cmd_main(radio, radio->curfreq, true);
	return 0;
}