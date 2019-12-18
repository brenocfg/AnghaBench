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
struct TYPE_3__ {int min_sof; } ;
struct TYPE_4__ {TYPE_1__ stream; } ;
struct uvc_streaming {TYPE_2__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void uvc_video_stats_start(struct uvc_streaming *stream)
{
	memset(&stream->stats, 0, sizeof(stream->stats));
	stream->stats.stream.min_sof = 2048;
}