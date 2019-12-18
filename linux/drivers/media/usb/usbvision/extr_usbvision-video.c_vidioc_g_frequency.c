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
struct v4l2_frequency {scalar_t__ type; int /*<<< orphan*/  frequency; scalar_t__ tuner; } ;
struct usb_usbvision {int /*<<< orphan*/  tv_freq; int /*<<< orphan*/  radio_freq; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
				struct v4l2_frequency *freq)
{
	struct usb_usbvision *usbvision = video_drvdata(file);

	/* Only one tuner */
	if (freq->tuner)
		return -EINVAL;
	if (freq->type == V4L2_TUNER_RADIO)
		freq->frequency = usbvision->radio_freq;
	else
		freq->frequency = usbvision->tv_freq;

	return 0;
}