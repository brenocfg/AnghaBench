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
struct file {struct dvb_device* private_data; } ;
struct dvb_device {int dummy; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  dvb_frontend_do_ioctl ; 
 long dvb_usercopy (struct file*,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long dvb_frontend_ioctl(struct file *file, unsigned int cmd,
			       unsigned long arg)
{
	struct dvb_device *dvbdev = file->private_data;

	if (!dvbdev)
		return -ENODEV;

	return dvb_usercopy(file, cmd, arg, dvb_frontend_do_ioctl);
}