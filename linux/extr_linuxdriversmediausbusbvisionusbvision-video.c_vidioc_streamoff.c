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
struct usb_usbvision {scalar_t__ streaming; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  call_all (struct usb_usbvision*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 scalar_t__ stream_on ; 
 int /*<<< orphan*/  usbvision_empty_framequeues (struct usb_usbvision*) ; 
 int /*<<< orphan*/  usbvision_stream_interrupt (struct usb_usbvision*) ; 
 int /*<<< orphan*/  video ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_streamoff(struct file *file,
			    void *priv, enum v4l2_buf_type type)
{
	struct usb_usbvision *usbvision = video_drvdata(file);

	if (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if (usbvision->streaming == stream_on) {
		usbvision_stream_interrupt(usbvision);
		/* Stop all video streamings */
		call_all(usbvision, video, s_stream, 0);
	}
	usbvision_empty_framequeues(usbvision);

	return 0;
}