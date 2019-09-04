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
typedef  int u8 ;
struct v4l2_rect {unsigned int top; unsigned int height; scalar_t__ left; scalar_t__ width; } ;
struct tpg_draw_params {unsigned int twopixsize; unsigned int img_width; unsigned int frame_line; unsigned int wss_width; int wss_random_offset; unsigned int left_pillar_width; unsigned int right_pillar_start; int sav_eav_f; int /*<<< orphan*/  is_60hz; scalar_t__ is_tv; } ;
struct TYPE_2__ {int width; } ;
struct tpg_data {int** random_line; int** contrast_line; scalar_t__ qual; int** black_line; TYPE_1__ compose; scalar_t__ insert_eav; scalar_t__ insert_sav; scalar_t__ show_square; scalar_t__ show_border; struct v4l2_rect crop; struct v4l2_rect border; struct v4l2_rect square; } ;

/* Variables and functions */
 scalar_t__ TPG_QUAL_NOISE ; 
 int /*<<< orphan*/  memcpy (int*,int*,unsigned int) ; 
 unsigned int tpg_hdiv (struct tpg_data const*,unsigned int,int) ; 
 unsigned int tpg_hscale_div (struct tpg_data const*,unsigned int,unsigned int) ; 

__attribute__((used)) static void tpg_fill_plane_extras(const struct tpg_data *tpg,
				  const struct tpg_draw_params *params,
				  unsigned p, unsigned h, u8 *vbuf)
{
	unsigned twopixsize = params->twopixsize;
	unsigned img_width = params->img_width;
	unsigned frame_line = params->frame_line;
	const struct v4l2_rect *sq = &tpg->square;
	const struct v4l2_rect *b = &tpg->border;
	const struct v4l2_rect *c = &tpg->crop;

	if (params->is_tv && !params->is_60hz &&
	    frame_line == 0 && params->wss_width) {
		/*
		 * Replace the first half of the top line of a 50 Hz frame
		 * with random data to simulate a WSS signal.
		 */
		u8 *wss = tpg->random_line[p] + params->wss_random_offset;

		memcpy(vbuf, wss, params->wss_width);
	}

	if (tpg->show_border && frame_line >= b->top &&
	    frame_line < b->top + b->height) {
		unsigned bottom = b->top + b->height - 1;
		unsigned left = params->left_pillar_width;
		unsigned right = params->right_pillar_start;

		if (frame_line == b->top || frame_line == b->top + 1 ||
		    frame_line == bottom || frame_line == bottom - 1) {
			memcpy(vbuf + left, tpg->contrast_line[p],
					right - left);
		} else {
			if (b->left >= c->left &&
			    b->left < c->left + c->width)
				memcpy(vbuf + left,
					tpg->contrast_line[p], twopixsize);
			if (b->left + b->width > c->left &&
			    b->left + b->width <= c->left + c->width)
				memcpy(vbuf + right - twopixsize,
					tpg->contrast_line[p], twopixsize);
		}
	}
	if (tpg->qual != TPG_QUAL_NOISE && frame_line >= b->top &&
	    frame_line < b->top + b->height) {
		memcpy(vbuf, tpg->black_line[p], params->left_pillar_width);
		memcpy(vbuf + params->right_pillar_start, tpg->black_line[p],
		       img_width - params->right_pillar_start);
	}
	if (tpg->show_square && frame_line >= sq->top &&
	    frame_line < sq->top + sq->height &&
	    sq->left < c->left + c->width &&
	    sq->left + sq->width >= c->left) {
		unsigned left = sq->left;
		unsigned width = sq->width;

		if (c->left > left) {
			width -= c->left - left;
			left = c->left;
		}
		if (c->left + c->width < left + width)
			width -= left + width - c->left - c->width;
		left -= c->left;
		left = tpg_hscale_div(tpg, p, left);
		width = tpg_hscale_div(tpg, p, width);
		memcpy(vbuf + left, tpg->contrast_line[p], width);
	}
	if (tpg->insert_sav) {
		unsigned offset = tpg_hdiv(tpg, p, tpg->compose.width / 3);
		u8 *p = vbuf + offset;
		unsigned vact = 0, hact = 0;

		p[0] = 0xff;
		p[1] = 0;
		p[2] = 0;
		p[3] = 0x80 | (params->sav_eav_f << 6) |
			(vact << 5) | (hact << 4) |
			((hact ^ vact) << 3) |
			((hact ^ params->sav_eav_f) << 2) |
			((params->sav_eav_f ^ vact) << 1) |
			(hact ^ vact ^ params->sav_eav_f);
	}
	if (tpg->insert_eav) {
		unsigned offset = tpg_hdiv(tpg, p, tpg->compose.width * 2 / 3);
		u8 *p = vbuf + offset;
		unsigned vact = 0, hact = 1;

		p[0] = 0xff;
		p[1] = 0;
		p[2] = 0;
		p[3] = 0x80 | (params->sav_eav_f << 6) |
			(vact << 5) | (hact << 4) |
			((hact ^ vact) << 3) |
			((hact ^ params->sav_eav_f) << 2) |
			((params->sav_eav_f ^ vact) << 1) |
			(hact ^ vact ^ params->sav_eav_f);
	}
}