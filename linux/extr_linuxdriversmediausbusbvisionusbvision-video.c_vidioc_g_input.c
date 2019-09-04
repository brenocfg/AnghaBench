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
struct usb_usbvision {unsigned int ctl_input; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_input(struct file *file, void *priv, unsigned int *input)
{
	struct usb_usbvision *usbvision = video_drvdata(file);

	*input = usbvision->ctl_input;
	return 0;
}