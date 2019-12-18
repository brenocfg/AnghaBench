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
struct uvc_streaming {int frozen; int /*<<< orphan*/  intfnum; TYPE_1__* dev; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_queue_streaming (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_video_stop_transfer (struct uvc_streaming*,int /*<<< orphan*/ ) ; 

int uvc_video_suspend(struct uvc_streaming *stream)
{
	if (!uvc_queue_streaming(&stream->queue))
		return 0;

	stream->frozen = 1;
	uvc_video_stop_transfer(stream, 0);
	usb_set_interface(stream->dev->udev, stream->intfnum, 0);
	return 0;
}