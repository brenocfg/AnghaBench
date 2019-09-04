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
struct em28xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  em28xx_resume_extension (struct em28xx*) ; 
 struct em28xx* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int em28xx_usb_resume(struct usb_interface *intf)
{
	struct em28xx *dev;

	dev = usb_get_intfdata(intf);
	if (!dev)
		return 0;
	em28xx_resume_extension(dev);
	return 0;
}