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
struct xbox_remote {int /*<<< orphan*/  irq_urb; } ;
struct rc_dev {struct xbox_remote* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xbox_remote_rc_close(struct rc_dev *rdev)
{
	struct xbox_remote *xbox_remote = rdev->priv;

	usb_kill_urb(xbox_remote->irq_urb);
}