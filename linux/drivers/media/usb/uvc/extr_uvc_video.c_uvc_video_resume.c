#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uvc_streaming {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  queue; scalar_t__ frozen; int /*<<< orphan*/  intfnum; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uvc_commit_video (struct uvc_streaming*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_queue_streaming (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_video_clock_reset (struct uvc_streaming*) ; 
 int uvc_video_start_transfer (struct uvc_streaming*,int /*<<< orphan*/ ) ; 

int uvc_video_resume(struct uvc_streaming *stream, int reset)
{
	int ret;

	/* If the bus has been reset on resume, set the alternate setting to 0.
	 * This should be the default value, but some devices crash or otherwise
	 * misbehave if they don't receive a SET_INTERFACE request before any
	 * other video control request.
	 */
	if (reset)
		usb_set_interface(stream->dev->udev, stream->intfnum, 0);

	stream->frozen = 0;

	uvc_video_clock_reset(stream);

	if (!uvc_queue_streaming(&stream->queue))
		return 0;

	ret = uvc_commit_video(stream, &stream->ctrl);
	if (ret < 0)
		return ret;

	return uvc_video_start_transfer(stream, GFP_NOIO);
}