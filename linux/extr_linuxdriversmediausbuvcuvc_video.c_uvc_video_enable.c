#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int bEndpointAddress; } ;
struct uvc_streaming {int /*<<< orphan*/  intfnum; TYPE_3__* dev; int /*<<< orphan*/  ctrl; TYPE_2__ header; TYPE_1__* intf; } ;
struct TYPE_6__ {int /*<<< orphan*/  udev; } ;
struct TYPE_4__ {int num_altsetting; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int USB_ENDPOINT_DIR_MASK ; 
 unsigned int USB_ENDPOINT_NUMBER_MASK ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndbulkpipe (int /*<<< orphan*/ ,unsigned int) ; 
 int uvc_commit_video (struct uvc_streaming*,int /*<<< orphan*/ *) ; 
 int uvc_init_video (struct uvc_streaming*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_uninit_video (struct uvc_streaming*,int) ; 
 int /*<<< orphan*/  uvc_video_clock_cleanup (struct uvc_streaming*) ; 
 int uvc_video_clock_init (struct uvc_streaming*) ; 

int uvc_video_enable(struct uvc_streaming *stream, int enable)
{
	int ret;

	if (!enable) {
		uvc_uninit_video(stream, 1);
		if (stream->intf->num_altsetting > 1) {
			usb_set_interface(stream->dev->udev,
					  stream->intfnum, 0);
		} else {
			/* UVC doesn't specify how to inform a bulk-based device
			 * when the video stream is stopped. Windows sends a
			 * CLEAR_FEATURE(HALT) request to the video streaming
			 * bulk endpoint, mimic the same behaviour.
			 */
			unsigned int epnum = stream->header.bEndpointAddress
					   & USB_ENDPOINT_NUMBER_MASK;
			unsigned int dir = stream->header.bEndpointAddress
					 & USB_ENDPOINT_DIR_MASK;
			unsigned int pipe;

			pipe = usb_sndbulkpipe(stream->dev->udev, epnum) | dir;
			usb_clear_halt(stream->dev->udev, pipe);
		}

		uvc_video_clock_cleanup(stream);
		return 0;
	}

	ret = uvc_video_clock_init(stream);
	if (ret < 0)
		return ret;

	/* Commit the streaming parameters. */
	ret = uvc_commit_video(stream, &stream->ctrl);
	if (ret < 0)
		goto error_commit;

	ret = uvc_init_video(stream, GFP_KERNEL);
	if (ret < 0)
		goto error_video;

	return 0;

error_video:
	usb_set_interface(stream->dev->udev, stream->intfnum, 0);
error_commit:
	uvc_video_clock_cleanup(stream);

	return ret;
}