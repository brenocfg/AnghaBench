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
typedef  int u8 ;
typedef  int u16 ;
struct tpg_data {int pattern; unsigned int src_width; unsigned int scaled_width; unsigned int planes; unsigned int* twopixelsize; unsigned int* hdownsampling; int*** lines; int* vdownsampling; int*** downsampled_lines; int** contrast_line; int** black_line; int** random_line; int** textbg; int** textfg; scalar_t__ hflip; } ;
typedef  enum tpg_color { ____Placeholder_tpg_color } tpg_color ;

/* Variables and functions */
 int TPG_COLOR_100_BLACK ; 
 int TPG_COLOR_100_GREEN ; 
 int TPG_COLOR_100_RED ; 
 int TPG_COLOR_CSC_GREEN ; 
 int TPG_COLOR_RANDOM ; 
 int TPG_COLOR_TEXTBG ; 
 int TPG_COLOR_TEXTFG ; 
 int TPG_MAX_PLANES ; 
#define  TPG_PAT_CSC_COLORBAR 129 
#define  TPG_PAT_GREEN 128 
 int /*<<< orphan*/  gen_twopix (struct tpg_data*,int**,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,unsigned int) ; 
 int tpg_get_color (struct tpg_data*,unsigned int,unsigned int) ; 
 unsigned int tpg_get_pat_lines (struct tpg_data*) ; 
 int tpg_hdiv (struct tpg_data*,unsigned int,int) ; 

__attribute__((used)) static void tpg_precalculate_line(struct tpg_data *tpg)
{
	enum tpg_color contrast;
	u8 pix[TPG_MAX_PLANES][8];
	unsigned pat;
	unsigned p;
	unsigned x;

	switch (tpg->pattern) {
	case TPG_PAT_GREEN:
		contrast = TPG_COLOR_100_RED;
		break;
	case TPG_PAT_CSC_COLORBAR:
		contrast = TPG_COLOR_CSC_GREEN;
		break;
	default:
		contrast = TPG_COLOR_100_GREEN;
		break;
	}

	for (pat = 0; pat < tpg_get_pat_lines(tpg); pat++) {
		/* Coarse scaling with Bresenham */
		unsigned int_part = tpg->src_width / tpg->scaled_width;
		unsigned fract_part = tpg->src_width % tpg->scaled_width;
		unsigned src_x = 0;
		unsigned error = 0;

		for (x = 0; x < tpg->scaled_width * 2; x += 2) {
			unsigned real_x = src_x;
			enum tpg_color color1, color2;

			real_x = tpg->hflip ? tpg->src_width * 2 - real_x - 2 : real_x;
			color1 = tpg_get_color(tpg, pat, real_x);

			src_x += int_part;
			error += fract_part;
			if (error >= tpg->scaled_width) {
				error -= tpg->scaled_width;
				src_x++;
			}

			real_x = src_x;
			real_x = tpg->hflip ? tpg->src_width * 2 - real_x - 2 : real_x;
			color2 = tpg_get_color(tpg, pat, real_x);

			src_x += int_part;
			error += fract_part;
			if (error >= tpg->scaled_width) {
				error -= tpg->scaled_width;
				src_x++;
			}

			gen_twopix(tpg, pix, tpg->hflip ? color2 : color1, 0);
			gen_twopix(tpg, pix, tpg->hflip ? color1 : color2, 1);
			for (p = 0; p < tpg->planes; p++) {
				unsigned twopixsize = tpg->twopixelsize[p];
				unsigned hdiv = tpg->hdownsampling[p];
				u8 *pos = tpg->lines[pat][p] + tpg_hdiv(tpg, p, x);

				memcpy(pos, pix[p], twopixsize / hdiv);
			}
		}
	}

	if (tpg->vdownsampling[tpg->planes - 1] > 1) {
		unsigned pat_lines = tpg_get_pat_lines(tpg);

		for (pat = 0; pat < pat_lines; pat++) {
			unsigned next_pat = (pat + 1) % pat_lines;

			for (p = 1; p < tpg->planes; p++) {
				unsigned w = tpg_hdiv(tpg, p, tpg->scaled_width * 2);
				u8 *pos1 = tpg->lines[pat][p];
				u8 *pos2 = tpg->lines[next_pat][p];
				u8 *dest = tpg->downsampled_lines[pat][p];

				for (x = 0; x < w; x++, pos1++, pos2++, dest++)
					*dest = ((u16)*pos1 + (u16)*pos2) / 2;
			}
		}
	}

	gen_twopix(tpg, pix, contrast, 0);
	gen_twopix(tpg, pix, contrast, 1);
	for (p = 0; p < tpg->planes; p++) {
		unsigned twopixsize = tpg->twopixelsize[p];
		u8 *pos = tpg->contrast_line[p];

		for (x = 0; x < tpg->scaled_width; x += 2, pos += twopixsize)
			memcpy(pos, pix[p], twopixsize);
	}

	gen_twopix(tpg, pix, TPG_COLOR_100_BLACK, 0);
	gen_twopix(tpg, pix, TPG_COLOR_100_BLACK, 1);
	for (p = 0; p < tpg->planes; p++) {
		unsigned twopixsize = tpg->twopixelsize[p];
		u8 *pos = tpg->black_line[p];

		for (x = 0; x < tpg->scaled_width; x += 2, pos += twopixsize)
			memcpy(pos, pix[p], twopixsize);
	}

	for (x = 0; x < tpg->scaled_width * 2; x += 2) {
		gen_twopix(tpg, pix, TPG_COLOR_RANDOM, 0);
		gen_twopix(tpg, pix, TPG_COLOR_RANDOM, 1);
		for (p = 0; p < tpg->planes; p++) {
			unsigned twopixsize = tpg->twopixelsize[p];
			u8 *pos = tpg->random_line[p] + x * twopixsize / 2;

			memcpy(pos, pix[p], twopixsize);
		}
	}

	gen_twopix(tpg, tpg->textbg, TPG_COLOR_TEXTBG, 0);
	gen_twopix(tpg, tpg->textbg, TPG_COLOR_TEXTBG, 1);
	gen_twopix(tpg, tpg->textfg, TPG_COLOR_TEXTFG, 0);
	gen_twopix(tpg, tpg->textfg, TPG_COLOR_TEXTFG, 1);
}