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
struct v4l2_tuner {scalar_t__ index; } ;
struct usb_usbvision {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  call_all (struct usb_usbvision*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner const*) ; 
 int /*<<< orphan*/  s_tuner ; 
 int /*<<< orphan*/  tuner ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_tuner(struct file *file, void *priv,
				const struct v4l2_tuner *vt)
{
	struct usb_usbvision *usbvision = video_drvdata(file);

	/* Only one tuner for now */
	if (vt->index)
		return -EINVAL;
	/* let clients handle this */
	call_all(usbvision, tuner, s_tuner, vt);

	return 0;
}