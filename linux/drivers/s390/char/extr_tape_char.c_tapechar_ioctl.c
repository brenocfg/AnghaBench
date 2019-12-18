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
struct tape_device {int /*<<< orphan*/  mutex; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*) ; 
 long __tapechar_ioctl (struct tape_device*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
tapechar_ioctl(struct file *filp, unsigned int no, unsigned long data)
{
	struct tape_device *device;
	long rc;

	DBF_EVENT(6, "TCHAR:ioct\n");

	device = (struct tape_device *) filp->private_data;
	mutex_lock(&device->mutex);
	rc = __tapechar_ioctl(device, no, data);
	mutex_unlock(&device->mutex);
	return rc;
}