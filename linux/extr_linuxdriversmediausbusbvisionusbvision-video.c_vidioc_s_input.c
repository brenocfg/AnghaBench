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
struct usb_usbvision {unsigned int video_inputs; int /*<<< orphan*/  curheight; int /*<<< orphan*/  curwidth; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  usbvision_muxsel (struct usb_usbvision*,unsigned int) ; 
 int /*<<< orphan*/  usbvision_set_input (struct usb_usbvision*) ; 
 int /*<<< orphan*/  usbvision_set_output (struct usb_usbvision*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_input(struct file *file, void *priv, unsigned int input)
{
	struct usb_usbvision *usbvision = video_drvdata(file);

	if (input >= usbvision->video_inputs)
		return -EINVAL;

	usbvision_muxsel(usbvision, input);
	usbvision_set_input(usbvision);
	usbvision_set_output(usbvision,
			     usbvision->curwidth,
			     usbvision->curheight);
	return 0;
}