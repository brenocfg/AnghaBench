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
struct hpet_dev {int /*<<< orphan*/  hd_async_queue; } ;
struct file {struct hpet_dev* private_data; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hpet_fasync(int fd, struct file *file, int on)
{
	struct hpet_dev *devp;

	devp = file->private_data;

	if (fasync_helper(fd, file, on, &devp->hd_async_queue) >= 0)
		return 0;
	else
		return -EIO;
}