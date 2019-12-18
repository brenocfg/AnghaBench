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
struct vm_area_struct {int dummy; } ;
struct usb_usbvision {int /*<<< orphan*/  v4l2_lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usbvision_mmap (struct file*,struct vm_area_struct*) ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int usbvision_v4l2_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct usb_usbvision *usbvision = video_drvdata(file);
	int res;

	if (mutex_lock_interruptible(&usbvision->v4l2_lock))
		return -ERESTARTSYS;
	res = usbvision_mmap(file, vma);
	mutex_unlock(&usbvision->v4l2_lock);
	return res;
}