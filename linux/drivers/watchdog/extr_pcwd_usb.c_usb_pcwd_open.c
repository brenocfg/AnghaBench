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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  is_active ; 
 int stream_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_pcwd_device ; 
 int /*<<< orphan*/  usb_pcwd_keepalive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pcwd_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_pcwd_open(struct inode *inode, struct file *file)
{
	/* /dev/watchdog can only be opened once */
	if (test_and_set_bit(0, &is_active))
		return -EBUSY;

	/* Activate */
	usb_pcwd_start(usb_pcwd_device);
	usb_pcwd_keepalive(usb_pcwd_device);
	return stream_open(inode, file);
}