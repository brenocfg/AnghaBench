#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iowarrior {TYPE_1__* interface; struct iowarrior* read_queue; int /*<<< orphan*/  int_in_urb; struct iowarrior* int_in_buffer; int /*<<< orphan*/  minor; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iowarrior*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_intf (TYPE_1__*) ; 

__attribute__((used)) static inline void iowarrior_delete(struct iowarrior *dev)
{
	dev_dbg(&dev->interface->dev, "minor %d\n", dev->minor);
	kfree(dev->int_in_buffer);
	usb_free_urb(dev->int_in_urb);
	kfree(dev->read_queue);
	usb_put_intf(dev->interface);
	kfree(dev);
}