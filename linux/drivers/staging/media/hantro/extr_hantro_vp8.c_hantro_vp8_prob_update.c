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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct v4l2_vp8_entropy_header {scalar_t__**** coeff_probs; scalar_t__** mv_probs; scalar_t__* uv_mode_probs; scalar_t__* y_mode_probs; } ;
struct TYPE_6__ {scalar_t__* segment_probs; } ;
struct v4l2_ctrl_vp8_frame_header {TYPE_3__ segment_header; scalar_t__ prob_gf; scalar_t__ prob_last; scalar_t__ prob_intra; scalar_t__ prob_skip_false; struct v4l2_vp8_entropy_header entropy_header; } ;
struct TYPE_4__ {scalar_t__* cpu; } ;
struct TYPE_5__ {TYPE_1__ prob_tbl; } ;
struct hantro_ctx {TYPE_2__ vp8_dec; } ;

/* Variables and functions */

void hantro_vp8_prob_update(struct hantro_ctx *ctx,
			    const struct v4l2_ctrl_vp8_frame_header *hdr)
{
	const struct v4l2_vp8_entropy_header *entropy = &hdr->entropy_header;
	u32 i, j, k;
	u8 *dst;

	/* first probs */
	dst = ctx->vp8_dec.prob_tbl.cpu;

	dst[0] = hdr->prob_skip_false;
	dst[1] = hdr->prob_intra;
	dst[2] = hdr->prob_last;
	dst[3] = hdr->prob_gf;
	dst[4] = hdr->segment_header.segment_probs[0];
	dst[5] = hdr->segment_header.segment_probs[1];
	dst[6] = hdr->segment_header.segment_probs[2];
	dst[7] = 0;

	dst += 8;
	dst[0] = entropy->y_mode_probs[0];
	dst[1] = entropy->y_mode_probs[1];
	dst[2] = entropy->y_mode_probs[2];
	dst[3] = entropy->y_mode_probs[3];
	dst[4] = entropy->uv_mode_probs[0];
	dst[5] = entropy->uv_mode_probs[1];
	dst[6] = entropy->uv_mode_probs[2];
	dst[7] = 0; /*unused */

	/* mv probs */
	dst += 8;
	dst[0] = entropy->mv_probs[0][0]; /* is short */
	dst[1] = entropy->mv_probs[1][0];
	dst[2] = entropy->mv_probs[0][1]; /* sign */
	dst[3] = entropy->mv_probs[1][1];
	dst[4] = entropy->mv_probs[0][8 + 9];
	dst[5] = entropy->mv_probs[0][9 + 9];
	dst[6] = entropy->mv_probs[1][8 + 9];
	dst[7] = entropy->mv_probs[1][9 + 9];
	dst += 8;
	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 8; j += 4) {
			dst[0] = entropy->mv_probs[i][j + 9 + 0];
			dst[1] = entropy->mv_probs[i][j + 9 + 1];
			dst[2] = entropy->mv_probs[i][j + 9 + 2];
			dst[3] = entropy->mv_probs[i][j + 9 + 3];
			dst += 4;
		}
	}
	for (i = 0; i < 2; ++i) {
		dst[0] = entropy->mv_probs[i][0 + 2];
		dst[1] = entropy->mv_probs[i][1 + 2];
		dst[2] = entropy->mv_probs[i][2 + 2];
		dst[3] = entropy->mv_probs[i][3 + 2];
		dst[4] = entropy->mv_probs[i][4 + 2];
		dst[5] = entropy->mv_probs[i][5 + 2];
		dst[6] = entropy->mv_probs[i][6 + 2];
		dst[7] = 0;	/*unused */
		dst += 8;
	}

	/* coeff probs (header part) */
	dst = ctx->vp8_dec.prob_tbl.cpu;
	dst += (8 * 7);
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 8; ++j) {
			for (k = 0; k < 3; ++k) {
				dst[0] = entropy->coeff_probs[i][j][k][0];
				dst[1] = entropy->coeff_probs[i][j][k][1];
				dst[2] = entropy->coeff_probs[i][j][k][2];
				dst[3] = entropy->coeff_probs[i][j][k][3];
				dst += 4;
			}
		}
	}

	/* coeff probs (footer part) */
	dst = ctx->vp8_dec.prob_tbl.cpu;
	dst += (8 * 55);
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 8; ++j) {
			for (k = 0; k < 3; ++k) {
				dst[0] = entropy->coeff_probs[i][j][k][4];
				dst[1] = entropy->coeff_probs[i][j][k][5];
				dst[2] = entropy->coeff_probs[i][j][k][6];
				dst[3] = entropy->coeff_probs[i][j][k][7];
				dst[4] = entropy->coeff_probs[i][j][k][8];
				dst[5] = entropy->coeff_probs[i][j][k][9];
				dst[6] = entropy->coeff_probs[i][j][k][10];
				dst[7] = 0;	/*unused */
				dst += 8;
			}
		}
	}
}