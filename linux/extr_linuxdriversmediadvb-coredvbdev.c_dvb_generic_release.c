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
struct file {int f_flags; struct dvb_device* private_data; } ;
struct dvb_device {int /*<<< orphan*/  users; int /*<<< orphan*/  writers; int /*<<< orphan*/  readers; } ;

/* Variables and functions */
 int ENODEV ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 

int dvb_generic_release(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;

	if (!dvbdev)
		return -ENODEV;

	if ((file->f_flags & O_ACCMODE) == O_RDONLY) {
		dvbdev->readers++;
	} else {
		dvbdev->writers++;
	}

	dvbdev->users++;
	return 0;
}