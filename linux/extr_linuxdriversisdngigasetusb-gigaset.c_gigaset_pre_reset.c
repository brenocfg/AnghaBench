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

/* Variables and functions */
 int /*<<< orphan*/  PMSG_ON ; 
 int gigaset_suspend (struct usb_interface*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gigaset_pre_reset(struct usb_interface *intf)
{
	/* same as suspend */
	return gigaset_suspend(intf, PMSG_ON);
}