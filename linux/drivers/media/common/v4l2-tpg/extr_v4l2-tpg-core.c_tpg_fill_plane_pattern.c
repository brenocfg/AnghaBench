#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tpg_draw_params {unsigned int twopixsize; unsigned int img_width; unsigned int mv_hor_old; unsigned int mv_hor_new; unsigned int mv_vert_old; unsigned int mv_vert_new; unsigned int frame_line; unsigned int frame_line_next; unsigned int hmax; scalar_t__ is_60hz; } ;
struct TYPE_6__ {unsigned int top; unsigned int height; } ;
struct TYPE_5__ {scalar_t__ height; } ;
struct TYPE_4__ {int /*<<< orphan*/  left; } ;
struct tpg_data {unsigned int src_height; scalar_t__ qual; scalar_t__ pattern; int src_width; int* vdownsampling; int field; scalar_t__ field_alternate; int /*<<< orphan*/ ** downsampled_lines; int /*<<< orphan*/ *** lines; int /*<<< orphan*/ ** random_line; int /*<<< orphan*/ ** black_line; TYPE_3__ border; int /*<<< orphan*/ ** contrast_line; scalar_t__ vflip; int /*<<< orphan*/  perc_fill_blank; TYPE_2__ compose; TYPE_1__ crop; } ;

/* Variables and functions */
 scalar_t__ TPG_PAT_NOISE ; 
 scalar_t__ TPG_QUAL_NOISE ; 
#define  V4L2_FIELD_BOTTOM 135 
#define  V4L2_FIELD_INTERLACED 134 
#define  V4L2_FIELD_INTERLACED_BT 133 
#define  V4L2_FIELD_INTERLACED_TB 132 
#define  V4L2_FIELD_NONE 131 
#define  V4L2_FIELD_SEQ_BT 130 
#define  V4L2_FIELD_SEQ_TB 129 
#define  V4L2_FIELD_TOP 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int prandom_u32_max (int) ; 
 unsigned int tpg_get_pat_line (struct tpg_data const*,unsigned int) ; 
 unsigned int tpg_hscale_div (struct tpg_data const*,unsigned int,int /*<<< orphan*/ ) ; 
 int tpg_pattern_avg (struct tpg_data const*,unsigned int,unsigned int) ; 

__attribute__((used)) static void tpg_fill_plane_pattern(const struct tpg_data *tpg,
				   const struct tpg_draw_params *params,
				   unsigned p, unsigned h, u8 *vbuf)
{
	unsigned twopixsize = params->twopixsize;
	unsigned img_width = params->img_width;
	unsigned mv_hor_old = params->mv_hor_old;
	unsigned mv_hor_new = params->mv_hor_new;
	unsigned mv_vert_old = params->mv_vert_old;
	unsigned mv_vert_new = params->mv_vert_new;
	unsigned frame_line = params->frame_line;
	unsigned frame_line_next = params->frame_line_next;
	unsigned line_offset = tpg_hscale_div(tpg, p, tpg->crop.left);
	bool even;
	bool fill_blank = false;
	unsigned pat_line_old;
	unsigned pat_line_new;
	u8 *linestart_older;
	u8 *linestart_newer;
	u8 *linestart_top;
	u8 *linestart_bottom;

	even = !(frame_line & 1);

	if (h >= params->hmax) {
		if (params->hmax == tpg->compose.height)
			return;
		if (!tpg->perc_fill_blank)
			return;
		fill_blank = true;
	}

	if (tpg->vflip) {
		frame_line = tpg->src_height - frame_line - 1;
		frame_line_next = tpg->src_height - frame_line_next - 1;
	}

	if (fill_blank) {
		linestart_older = tpg->contrast_line[p];
		linestart_newer = tpg->contrast_line[p];
	} else if (tpg->qual != TPG_QUAL_NOISE &&
		   (frame_line < tpg->border.top ||
		    frame_line >= tpg->border.top + tpg->border.height)) {
		linestart_older = tpg->black_line[p];
		linestart_newer = tpg->black_line[p];
	} else if (tpg->pattern == TPG_PAT_NOISE || tpg->qual == TPG_QUAL_NOISE) {
		linestart_older = tpg->random_line[p] +
				  twopixsize * prandom_u32_max(tpg->src_width / 2);
		linestart_newer = tpg->random_line[p] +
				  twopixsize * prandom_u32_max(tpg->src_width / 2);
	} else {
		unsigned frame_line_old =
			(frame_line + mv_vert_old) % tpg->src_height;
		unsigned frame_line_new =
			(frame_line + mv_vert_new) % tpg->src_height;
		unsigned pat_line_next_old;
		unsigned pat_line_next_new;

		pat_line_old = tpg_get_pat_line(tpg, frame_line_old);
		pat_line_new = tpg_get_pat_line(tpg, frame_line_new);
		linestart_older = tpg->lines[pat_line_old][p] + mv_hor_old;
		linestart_newer = tpg->lines[pat_line_new][p] + mv_hor_new;

		if (tpg->vdownsampling[p] > 1 && frame_line != frame_line_next) {
			int avg_pat;

			/*
			 * Now decide whether we need to use downsampled_lines[].
			 * That's necessary if the two lines use different patterns.
			 */
			pat_line_next_old = tpg_get_pat_line(tpg,
					(frame_line_next + mv_vert_old) % tpg->src_height);
			pat_line_next_new = tpg_get_pat_line(tpg,
					(frame_line_next + mv_vert_new) % tpg->src_height);

			switch (tpg->field) {
			case V4L2_FIELD_INTERLACED:
			case V4L2_FIELD_INTERLACED_BT:
			case V4L2_FIELD_INTERLACED_TB:
				avg_pat = tpg_pattern_avg(tpg, pat_line_old, pat_line_new);
				if (avg_pat < 0)
					break;
				linestart_older = tpg->downsampled_lines[avg_pat][p] + mv_hor_old;
				linestart_newer = linestart_older;
				break;
			case V4L2_FIELD_NONE:
			case V4L2_FIELD_TOP:
			case V4L2_FIELD_BOTTOM:
			case V4L2_FIELD_SEQ_BT:
			case V4L2_FIELD_SEQ_TB:
				avg_pat = tpg_pattern_avg(tpg, pat_line_old, pat_line_next_old);
				if (avg_pat >= 0)
					linestart_older = tpg->downsampled_lines[avg_pat][p] +
						mv_hor_old;
				avg_pat = tpg_pattern_avg(tpg, pat_line_new, pat_line_next_new);
				if (avg_pat >= 0)
					linestart_newer = tpg->downsampled_lines[avg_pat][p] +
						mv_hor_new;
				break;
			}
		}
		linestart_older += line_offset;
		linestart_newer += line_offset;
	}
	if (tpg->field_alternate) {
		linestart_top = linestart_bottom = linestart_older;
	} else if (params->is_60hz) {
		linestart_top = linestart_newer;
		linestart_bottom = linestart_older;
	} else {
		linestart_top = linestart_older;
		linestart_bottom = linestart_newer;
	}

	switch (tpg->field) {
	case V4L2_FIELD_INTERLACED:
	case V4L2_FIELD_INTERLACED_TB:
	case V4L2_FIELD_SEQ_TB:
	case V4L2_FIELD_SEQ_BT:
		if (even)
			memcpy(vbuf, linestart_top, img_width);
		else
			memcpy(vbuf, linestart_bottom, img_width);
		break;
	case V4L2_FIELD_INTERLACED_BT:
		if (even)
			memcpy(vbuf, linestart_bottom, img_width);
		else
			memcpy(vbuf, linestart_top, img_width);
		break;
	case V4L2_FIELD_TOP:
		memcpy(vbuf, linestart_top, img_width);
		break;
	case V4L2_FIELD_BOTTOM:
		memcpy(vbuf, linestart_bottom, img_width);
		break;
	case V4L2_FIELD_NONE:
	default:
		memcpy(vbuf, linestart_older, img_width);
		break;
	}
}