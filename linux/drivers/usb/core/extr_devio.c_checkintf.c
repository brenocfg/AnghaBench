#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_dev_state {TYPE_1__* dev; int /*<<< orphan*/  ifclaimed; } ;
struct TYPE_5__ {int /*<<< orphan*/  comm; } ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int EINVAL ; 
 scalar_t__ USB_STATE_CONFIGURED ; 
 int claimintf (struct usb_dev_state*,unsigned int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_2__*) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int checkintf(struct usb_dev_state *ps, unsigned int ifnum)
{
	if (ps->dev->state != USB_STATE_CONFIGURED)
		return -EHOSTUNREACH;
	if (ifnum >= 8*sizeof(ps->ifclaimed))
		return -EINVAL;
	if (test_bit(ifnum, &ps->ifclaimed))
		return 0;
	/* if not yet claimed, claim it for the driver */
	dev_warn(&ps->dev->dev, "usbfs: process %d (%s) did not claim "
		 "interface %u before use\n", task_pid_nr(current),
		 current->comm, ifnum);
	return claimintf(ps, ifnum);
}