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
struct TYPE_3__ {int scr_sof_count; int /*<<< orphan*/  max_sof; int /*<<< orphan*/  min_sof; int /*<<< orphan*/  nb_scr_diffs_ok; int /*<<< orphan*/  nb_scr_count_ok; int /*<<< orphan*/  nb_pts_constant; int /*<<< orphan*/  nb_pts_initial; int /*<<< orphan*/  nb_pts_early; int /*<<< orphan*/  nb_invalid; int /*<<< orphan*/  nb_errors; int /*<<< orphan*/  nb_empty; int /*<<< orphan*/  nb_packets; int /*<<< orphan*/  nb_frames; int /*<<< orphan*/  start_ts; int /*<<< orphan*/  stop_ts; } ;
struct TYPE_4__ {TYPE_1__ stream; } ;
struct uvc_streaming {TYPE_2__ stats; } ;

/* Variables and functions */
 unsigned int ktime_ms_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

size_t uvc_video_stats_dump(struct uvc_streaming *stream, char *buf,
			    size_t size)
{
	unsigned int scr_sof_freq;
	unsigned int duration;
	size_t count = 0;

	/* Compute the SCR.SOF frequency estimate. At the nominal 1kHz SOF
	 * frequency this will not overflow before more than 1h.
	 */
	duration = ktime_ms_delta(stream->stats.stream.stop_ts,
				  stream->stats.stream.start_ts);
	if (duration != 0)
		scr_sof_freq = stream->stats.stream.scr_sof_count * 1000
			     / duration;
	else
		scr_sof_freq = 0;

	count += scnprintf(buf + count, size - count,
			   "frames:  %u\npackets: %u\nempty:   %u\n"
			   "errors:  %u\ninvalid: %u\n",
			   stream->stats.stream.nb_frames,
			   stream->stats.stream.nb_packets,
			   stream->stats.stream.nb_empty,
			   stream->stats.stream.nb_errors,
			   stream->stats.stream.nb_invalid);
	count += scnprintf(buf + count, size - count,
			   "pts: %u early, %u initial, %u ok\n",
			   stream->stats.stream.nb_pts_early,
			   stream->stats.stream.nb_pts_initial,
			   stream->stats.stream.nb_pts_constant);
	count += scnprintf(buf + count, size - count,
			   "scr: %u count ok, %u diff ok\n",
			   stream->stats.stream.nb_scr_count_ok,
			   stream->stats.stream.nb_scr_diffs_ok);
	count += scnprintf(buf + count, size - count,
			   "sof: %u <= sof <= %u, freq %u.%03u kHz\n",
			   stream->stats.stream.min_sof,
			   stream->stats.stream.max_sof,
			   scr_sof_freq / 1000, scr_sof_freq % 1000);

	return count;
}