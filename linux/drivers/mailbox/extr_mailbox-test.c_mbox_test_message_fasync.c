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
struct mbox_test_device {int /*<<< orphan*/  async_queue; } ;
struct file {struct mbox_test_device* private_data; } ;

/* Variables and functions */
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mbox_test_message_fasync(int fd, struct file *filp, int on)
{
	struct mbox_test_device *tdev = filp->private_data;

	return fasync_helper(fd, filp, on, &tdev->async_queue);
}