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
struct uvc_clock {int last_sof; int sof_offset; scalar_t__ count; scalar_t__ head; } ;
struct uvc_streaming {struct uvc_clock clock; } ;

/* Variables and functions */

__attribute__((used)) static void uvc_video_clock_reset(struct uvc_streaming *stream)
{
	struct uvc_clock *clock = &stream->clock;

	clock->head = 0;
	clock->count = 0;
	clock->last_sof = -1;
	clock->sof_offset = -1;
}