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
struct cx2341x_handler {int /*<<< orphan*/  video_bitrate_peak; int /*<<< orphan*/  video_bitrate; int /*<<< orphan*/  video_bitrate_mode; int /*<<< orphan*/  stream_type; int /*<<< orphan*/  stream_vbi_fmt; int /*<<< orphan*/  audio_ac3_bitrate; int /*<<< orphan*/  audio_l2_bitrate; int /*<<< orphan*/  audio_encoding; int /*<<< orphan*/  audio_sampling_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 

void cx2341x_handler_set_busy(struct cx2341x_handler *cxhdl, int busy)
{
	v4l2_ctrl_grab(cxhdl->audio_sampling_freq, busy);
	v4l2_ctrl_grab(cxhdl->audio_encoding, busy);
	v4l2_ctrl_grab(cxhdl->audio_l2_bitrate, busy);
	v4l2_ctrl_grab(cxhdl->audio_ac3_bitrate, busy);
	v4l2_ctrl_grab(cxhdl->stream_vbi_fmt, busy);
	v4l2_ctrl_grab(cxhdl->stream_type, busy);
	v4l2_ctrl_grab(cxhdl->video_bitrate_mode, busy);
	v4l2_ctrl_grab(cxhdl->video_bitrate, busy);
	v4l2_ctrl_grab(cxhdl->video_bitrate_peak, busy);
}