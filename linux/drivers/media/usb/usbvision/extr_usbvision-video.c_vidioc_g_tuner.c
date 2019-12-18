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
struct v4l2_tuner {scalar_t__ type; int /*<<< orphan*/  name; scalar_t__ index; } ;
struct usb_usbvision {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  call_all (struct usb_usbvision*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 
 int /*<<< orphan*/  g_tuner ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tuner ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_tuner(struct file *file, void *priv,
				struct v4l2_tuner *vt)
{
	struct usb_usbvision *usbvision = video_drvdata(file);

	if (vt->index)	/* Only tuner 0 */
		return -EINVAL;
	if (vt->type == V4L2_TUNER_RADIO)
		strscpy(vt->name, "Radio", sizeof(vt->name));
	else
		strscpy(vt->name, "Television", sizeof(vt->name));

	/* Let clients fill in the remainder of this struct */
	call_all(usbvision, tuner, g_tuner, vt);

	return 0;
}