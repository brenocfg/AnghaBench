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
struct uvc_streaming {TYPE_1__* dev; } ;
struct TYPE_2__ {int uvc_version; } ;

/* Variables and functions */

__attribute__((used)) static size_t uvc_video_ctrl_size(struct uvc_streaming *stream)
{
	/*
	 * Return the size of the video probe and commit controls, which depends
	 * on the protocol version.
	 */
	if (stream->dev->uvc_version < 0x0110)
		return 26;
	else if (stream->dev->uvc_version < 0x0150)
		return 34;
	else
		return 48;
}