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
struct vc_data {size_t vc_num; unsigned int vc_rows; unsigned int vc_cols; unsigned int vc_size_row; int /*<<< orphan*/  vc_video_erase_char; int /*<<< orphan*/  vc_origin; } ;
struct fbcon_display {int vrows; int /*<<< orphan*/  yscroll; int /*<<< orphan*/  scrollmode; } ;
struct fb_info {int flags; } ;
typedef  enum con_scroll { ____Placeholder_con_scroll } con_scroll ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ERASE ; 
 int FBINFO_PARTIAL_PAN_OK ; 
 int FBINFO_READS_FAST ; 
#define  SCROLL_MOVE 134 
#define  SCROLL_PAN_MOVE 133 
#define  SCROLL_PAN_REDRAW 132 
#define  SCROLL_REDRAW 131 
#define  SCROLL_WRAP_MOVE 130 
#define  SM_DOWN 129 
#define  SM_UP 128 
 size_t* con2fb_map ; 
 struct fbcon_display* fb_display ; 
 int /*<<< orphan*/  fbcon_bmove (struct vc_data*,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fbcon_clear (struct vc_data*,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fbcon_cursor (struct vc_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ fbcon_is_inactive (struct vc_data*,struct fb_info*) ; 
 int /*<<< orphan*/  fbcon_redraw (struct vc_data*,struct fbcon_display*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fbcon_redraw_blit (struct vc_data*,struct fb_info*,struct fbcon_display*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fbcon_redraw_move (struct vc_data*,struct fbcon_display*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fbcon_softback_note (struct vc_data*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  logo_shown ; 
 struct fb_info** registered_fb ; 
 int /*<<< orphan*/  scr_memsetw (unsigned short*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  softback_top ; 
 int /*<<< orphan*/  ypan_down (struct vc_data*,unsigned int) ; 
 int /*<<< orphan*/  ypan_down_redraw (struct vc_data*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ypan_up (struct vc_data*,unsigned int) ; 
 int /*<<< orphan*/  ypan_up_redraw (struct vc_data*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ywrap_down (struct vc_data*,unsigned int) ; 
 int /*<<< orphan*/  ywrap_up (struct vc_data*,unsigned int) ; 

__attribute__((used)) static bool fbcon_scroll(struct vc_data *vc, unsigned int t, unsigned int b,
		enum con_scroll dir, unsigned int count)
{
	struct fb_info *info = registered_fb[con2fb_map[vc->vc_num]];
	struct fbcon_display *p = &fb_display[vc->vc_num];
	int scroll_partial = info->flags & FBINFO_PARTIAL_PAN_OK;

	if (fbcon_is_inactive(vc, info))
		return true;

	fbcon_cursor(vc, CM_ERASE);

	/*
	 * ++Geert: Only use ywrap/ypan if the console is in text mode
	 * ++Andrew: Only use ypan on hardware text mode when scrolling the
	 *           whole screen (prevents flicker).
	 */

	switch (dir) {
	case SM_UP:
		if (count > vc->vc_rows)	/* Maximum realistic size */
			count = vc->vc_rows;
		if (softback_top)
			fbcon_softback_note(vc, t, count);
		if (logo_shown >= 0)
			goto redraw_up;
		switch (p->scrollmode) {
		case SCROLL_MOVE:
			fbcon_redraw_blit(vc, info, p, t, b - t - count,
				     count);
			fbcon_clear(vc, b - count, 0, count, vc->vc_cols);
			scr_memsetw((unsigned short *) (vc->vc_origin +
							vc->vc_size_row *
							(b - count)),
				    vc->vc_video_erase_char,
				    vc->vc_size_row * count);
			return true;
			break;

		case SCROLL_WRAP_MOVE:
			if (b - t - count > 3 * vc->vc_rows >> 2) {
				if (t > 0)
					fbcon_bmove(vc, 0, 0, count, 0, t,
						    vc->vc_cols);
				ywrap_up(vc, count);
				if (vc->vc_rows - b > 0)
					fbcon_bmove(vc, b - count, 0, b, 0,
						    vc->vc_rows - b,
						    vc->vc_cols);
			} else if (info->flags & FBINFO_READS_FAST)
				fbcon_bmove(vc, t + count, 0, t, 0,
					    b - t - count, vc->vc_cols);
			else
				goto redraw_up;
			fbcon_clear(vc, b - count, 0, count, vc->vc_cols);
			break;

		case SCROLL_PAN_REDRAW:
			if ((p->yscroll + count <=
			     2 * (p->vrows - vc->vc_rows))
			    && ((!scroll_partial && (b - t == vc->vc_rows))
				|| (scroll_partial
				    && (b - t - count >
					3 * vc->vc_rows >> 2)))) {
				if (t > 0)
					fbcon_redraw_move(vc, p, 0, t, count);
				ypan_up_redraw(vc, t, count);
				if (vc->vc_rows - b > 0)
					fbcon_redraw_move(vc, p, b,
							  vc->vc_rows - b, b);
			} else
				fbcon_redraw_move(vc, p, t + count, b - t - count, t);
			fbcon_clear(vc, b - count, 0, count, vc->vc_cols);
			break;

		case SCROLL_PAN_MOVE:
			if ((p->yscroll + count <=
			     2 * (p->vrows - vc->vc_rows))
			    && ((!scroll_partial && (b - t == vc->vc_rows))
				|| (scroll_partial
				    && (b - t - count >
					3 * vc->vc_rows >> 2)))) {
				if (t > 0)
					fbcon_bmove(vc, 0, 0, count, 0, t,
						    vc->vc_cols);
				ypan_up(vc, count);
				if (vc->vc_rows - b > 0)
					fbcon_bmove(vc, b - count, 0, b, 0,
						    vc->vc_rows - b,
						    vc->vc_cols);
			} else if (info->flags & FBINFO_READS_FAST)
				fbcon_bmove(vc, t + count, 0, t, 0,
					    b - t - count, vc->vc_cols);
			else
				goto redraw_up;
			fbcon_clear(vc, b - count, 0, count, vc->vc_cols);
			break;

		case SCROLL_REDRAW:
		      redraw_up:
			fbcon_redraw(vc, p, t, b - t - count,
				     count * vc->vc_cols);
			fbcon_clear(vc, b - count, 0, count, vc->vc_cols);
			scr_memsetw((unsigned short *) (vc->vc_origin +
							vc->vc_size_row *
							(b - count)),
				    vc->vc_video_erase_char,
				    vc->vc_size_row * count);
			return true;
		}
		break;

	case SM_DOWN:
		if (count > vc->vc_rows)	/* Maximum realistic size */
			count = vc->vc_rows;
		if (logo_shown >= 0)
			goto redraw_down;
		switch (p->scrollmode) {
		case SCROLL_MOVE:
			fbcon_redraw_blit(vc, info, p, b - 1, b - t - count,
				     -count);
			fbcon_clear(vc, t, 0, count, vc->vc_cols);
			scr_memsetw((unsigned short *) (vc->vc_origin +
							vc->vc_size_row *
							t),
				    vc->vc_video_erase_char,
				    vc->vc_size_row * count);
			return true;
			break;

		case SCROLL_WRAP_MOVE:
			if (b - t - count > 3 * vc->vc_rows >> 2) {
				if (vc->vc_rows - b > 0)
					fbcon_bmove(vc, b, 0, b - count, 0,
						    vc->vc_rows - b,
						    vc->vc_cols);
				ywrap_down(vc, count);
				if (t > 0)
					fbcon_bmove(vc, count, 0, 0, 0, t,
						    vc->vc_cols);
			} else if (info->flags & FBINFO_READS_FAST)
				fbcon_bmove(vc, t, 0, t + count, 0,
					    b - t - count, vc->vc_cols);
			else
				goto redraw_down;
			fbcon_clear(vc, t, 0, count, vc->vc_cols);
			break;

		case SCROLL_PAN_MOVE:
			if ((count - p->yscroll <= p->vrows - vc->vc_rows)
			    && ((!scroll_partial && (b - t == vc->vc_rows))
				|| (scroll_partial
				    && (b - t - count >
					3 * vc->vc_rows >> 2)))) {
				if (vc->vc_rows - b > 0)
					fbcon_bmove(vc, b, 0, b - count, 0,
						    vc->vc_rows - b,
						    vc->vc_cols);
				ypan_down(vc, count);
				if (t > 0)
					fbcon_bmove(vc, count, 0, 0, 0, t,
						    vc->vc_cols);
			} else if (info->flags & FBINFO_READS_FAST)
				fbcon_bmove(vc, t, 0, t + count, 0,
					    b - t - count, vc->vc_cols);
			else
				goto redraw_down;
			fbcon_clear(vc, t, 0, count, vc->vc_cols);
			break;

		case SCROLL_PAN_REDRAW:
			if ((count - p->yscroll <= p->vrows - vc->vc_rows)
			    && ((!scroll_partial && (b - t == vc->vc_rows))
				|| (scroll_partial
				    && (b - t - count >
					3 * vc->vc_rows >> 2)))) {
				if (vc->vc_rows - b > 0)
					fbcon_redraw_move(vc, p, b, vc->vc_rows - b,
							  b - count);
				ypan_down_redraw(vc, t, count);
				if (t > 0)
					fbcon_redraw_move(vc, p, count, t, 0);
			} else
				fbcon_redraw_move(vc, p, t, b - t - count, t + count);
			fbcon_clear(vc, t, 0, count, vc->vc_cols);
			break;

		case SCROLL_REDRAW:
		      redraw_down:
			fbcon_redraw(vc, p, b - 1, b - t - count,
				     -count * vc->vc_cols);
			fbcon_clear(vc, t, 0, count, vc->vc_cols);
			scr_memsetw((unsigned short *) (vc->vc_origin +
							vc->vc_size_row *
							t),
				    vc->vc_video_erase_char,
				    vc->vc_size_row * count);
			return true;
		}
	}
	return false;
}