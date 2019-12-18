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
struct uvc_streaming {int /*<<< orphan*/  intfnum; TYPE_1__* dev; int /*<<< orphan*/  ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uvc_commit_video (struct uvc_streaming*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_video_clock_cleanup (struct uvc_streaming*) ; 
 int uvc_video_clock_init (struct uvc_streaming*) ; 
 int uvc_video_start_transfer (struct uvc_streaming*,int /*<<< orphan*/ ) ; 

int uvc_video_start_streaming(struct uvc_streaming *stream)
{
	int ret;

	ret = uvc_video_clock_init(stream);
	if (ret < 0)
		return ret;

	/* Commit the streaming parameters. */
	ret = uvc_commit_video(stream, &stream->ctrl);
	if (ret < 0)
		goto error_commit;

	ret = uvc_video_start_transfer(stream, GFP_KERNEL);
	if (ret < 0)
		goto error_video;

	return 0;

error_video:
	usb_set_interface(stream->dev->udev, stream->intfnum, 0);
error_commit:
	uvc_video_clock_cleanup(stream);

	return ret;
}