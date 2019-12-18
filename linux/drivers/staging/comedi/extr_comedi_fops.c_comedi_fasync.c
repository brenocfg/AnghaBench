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
struct file {struct comedi_file* private_data; } ;
struct comedi_file {struct comedi_device* dev; } ;
struct comedi_device {int /*<<< orphan*/  async_queue; } ;

/* Variables and functions */
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int comedi_fasync(int fd, struct file *file, int on)
{
	struct comedi_file *cfp = file->private_data;
	struct comedi_device *dev = cfp->dev;

	return fasync_helper(fd, file, on, &dev->async_queue);
}