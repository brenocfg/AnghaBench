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
typedef  int /*<<< orphan*/  u8 ;
struct vivid_vbi_gen_data {struct v4l2_sliced_vbi_data* data; } ;
struct v4l2_vbi_format {int flags; unsigned int samples_per_line; unsigned int* count; int /*<<< orphan*/  sampling_rate; scalar_t__* start; } ;
struct v4l2_sliced_vbi_data {unsigned int line; int id; int field; } ;

/* Variables and functions */
 int V4L2_SLICED_CAPTION_525 ; 
 int V4L2_SLICED_TELETEXT_B ; 
 int V4L2_SLICED_VBI_525 ; 
 int V4L2_SLICED_WSS_625 ; 
 int V4L2_VBI_INTERLACED ; 
 int /*<<< orphan*/  vivid_vbi_gen_cc_raw (struct v4l2_sliced_vbi_data const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vivid_vbi_gen_teletext_raw (struct v4l2_sliced_vbi_data const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vivid_vbi_gen_wss_raw (struct v4l2_sliced_vbi_data const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vivid_vbi_gen_raw(const struct vivid_vbi_gen_data *vbi,
		const struct v4l2_vbi_format *vbi_fmt, u8 *buf)
{
	unsigned idx;

	for (idx = 0; idx < 25; idx++) {
		const struct v4l2_sliced_vbi_data *data = vbi->data + idx;
		unsigned start_2nd_field;
		unsigned line = data->line;
		u8 *linebuf = buf;

		start_2nd_field = (data->id & V4L2_SLICED_VBI_525) ? 263 : 313;
		if (data->field)
			line += start_2nd_field;
		line -= vbi_fmt->start[data->field];

		if (vbi_fmt->flags & V4L2_VBI_INTERLACED)
			linebuf += (line * 2 + data->field) *
				vbi_fmt->samples_per_line;
		else
			linebuf += (line + data->field * vbi_fmt->count[0]) *
				vbi_fmt->samples_per_line;
		if (data->id == V4L2_SLICED_CAPTION_525)
			vivid_vbi_gen_cc_raw(data, linebuf, vbi_fmt->sampling_rate);
		else if (data->id == V4L2_SLICED_WSS_625)
			vivid_vbi_gen_wss_raw(data, linebuf, vbi_fmt->sampling_rate);
		else if (data->id == V4L2_SLICED_TELETEXT_B)
			vivid_vbi_gen_teletext_raw(data, linebuf, vbi_fmt->sampling_rate);
	}
}