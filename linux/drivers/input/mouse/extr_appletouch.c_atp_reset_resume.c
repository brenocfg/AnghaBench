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
struct atp {int dummy; } ;

/* Variables and functions */
 int atp_recover (struct atp*) ; 
 struct atp* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int atp_reset_resume(struct usb_interface *iface)
{
	struct atp *dev = usb_get_intfdata(iface);

	return atp_recover(dev);
}