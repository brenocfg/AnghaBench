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
struct uvc_stats_frame {scalar_t__ first_data; scalar_t__ nb_packets; scalar_t__ nb_empty; scalar_t__ last_pts_diff; scalar_t__ nb_scr_diffs; scalar_t__ nb_scr; scalar_t__ has_initial_pts; scalar_t__ has_early_pts; scalar_t__ nb_invalid; scalar_t__ nb_errors; int /*<<< orphan*/  scr_sof; int /*<<< orphan*/  scr_stc; int /*<<< orphan*/  pts; int /*<<< orphan*/  nb_pts; int /*<<< orphan*/  nb_pts_diffs; } ;
struct TYPE_3__ {int /*<<< orphan*/  nb_scr_diffs_ok; int /*<<< orphan*/  nb_scr_count_ok; int /*<<< orphan*/  nb_pts_constant; int /*<<< orphan*/  nb_pts_initial; int /*<<< orphan*/  nb_pts_early; int /*<<< orphan*/  nb_invalid; int /*<<< orphan*/  nb_errors; int /*<<< orphan*/  nb_empty; int /*<<< orphan*/  nb_packets; int /*<<< orphan*/  nb_frames; } ;
struct TYPE_4__ {struct uvc_stats_frame frame; TYPE_1__ stream; } ;
struct uvc_streaming {TYPE_2__ stats; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_TRACE_STATS ; 
 int /*<<< orphan*/  memset (struct uvc_stats_frame*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uvc_video_stats_update(struct uvc_streaming *stream)
{
	struct uvc_stats_frame *frame = &stream->stats.frame;

	uvc_trace(UVC_TRACE_STATS, "frame %u stats: %u/%u/%u packets, "
		  "%u/%u/%u pts (%searly %sinitial), %u/%u scr, "
		  "last pts/stc/sof %u/%u/%u\n",
		  stream->sequence, frame->first_data,
		  frame->nb_packets - frame->nb_empty, frame->nb_packets,
		  frame->nb_pts_diffs, frame->last_pts_diff, frame->nb_pts,
		  frame->has_early_pts ? "" : "!",
		  frame->has_initial_pts ? "" : "!",
		  frame->nb_scr_diffs, frame->nb_scr,
		  frame->pts, frame->scr_stc, frame->scr_sof);

	stream->stats.stream.nb_frames++;
	stream->stats.stream.nb_packets += stream->stats.frame.nb_packets;
	stream->stats.stream.nb_empty += stream->stats.frame.nb_empty;
	stream->stats.stream.nb_errors += stream->stats.frame.nb_errors;
	stream->stats.stream.nb_invalid += stream->stats.frame.nb_invalid;

	if (frame->has_early_pts)
		stream->stats.stream.nb_pts_early++;
	if (frame->has_initial_pts)
		stream->stats.stream.nb_pts_initial++;
	if (frame->last_pts_diff <= frame->first_data)
		stream->stats.stream.nb_pts_constant++;
	if (frame->nb_scr >= frame->nb_packets - frame->nb_empty)
		stream->stats.stream.nb_scr_count_ok++;
	if (frame->nb_scr_diffs + 1 == frame->nb_scr)
		stream->stats.stream.nb_scr_diffs_ok++;

	memset(&stream->stats.frame, 0, sizeof(stream->stats.frame));
}