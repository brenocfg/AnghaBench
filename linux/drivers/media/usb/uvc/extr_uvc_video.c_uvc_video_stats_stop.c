#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  stop_ts; } ;
struct TYPE_4__ {TYPE_1__ stream; } ;
struct uvc_streaming {TYPE_2__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void uvc_video_stats_stop(struct uvc_streaming *stream)
{
	stream->stats.stream.stop_ts = ktime_get();
}