#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct hubbub {int dummy; } ;
struct TYPE_10__ {TYPE_2__* funcs; TYPE_1__* ctx; } ;
struct dcn10_hubbub {TYPE_3__ base; } ;
struct TYPE_13__ {int max_uncompressed_blk_size; int max_compressed_blk_size; int independent_64b_blks; } ;
struct TYPE_14__ {TYPE_6__ rgb; } ;
struct dc_surface_dcc_cap {int capable; int const_color_support; TYPE_7__ grph; } ;
struct TYPE_11__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct dc_dcc_surface_param {scalar_t__ scan; TYPE_4__ surface_size; int /*<<< orphan*/  swizzle_mode; int /*<<< orphan*/  format; } ;
struct TYPE_12__ {scalar_t__ disable_dcc; } ;
struct dc {TYPE_5__ debug; } ;
typedef  enum segment_order { ____Placeholder_segment_order } segment_order ;
typedef  enum dcc_control { ____Placeholder_dcc_control } dcc_control ;
struct TYPE_9__ {int /*<<< orphan*/  (* dcc_support_swizzle ) (int /*<<< orphan*/ ,unsigned int,int*,int*) ;int /*<<< orphan*/  (* dcc_support_pixel_format ) (int /*<<< orphan*/ ,unsigned int*) ;} ;
struct TYPE_8__ {struct dc* dc; } ;

/* Variables and functions */
 scalar_t__ DCC_DISABLE ; 
 scalar_t__ DCC_HALF_REQ_DISALBE ; 
 scalar_t__ SCAN_DIRECTION_HORIZONTAL ; 
 scalar_t__ SCAN_DIRECTION_VERTICAL ; 
 struct dcn10_hubbub* TO_DCN10_HUBBUB (struct hubbub*) ; 
#define  dcc_control__128_128_xxx 130 
#define  dcc_control__256_256_xxx 129 
#define  dcc_control__256_64_64 128 
 int /*<<< orphan*/  hubbub1_det_request_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int*,int*) ; 
 int /*<<< orphan*/  memset (struct dc_surface_dcc_cap*,int /*<<< orphan*/ ,int) ; 
 int segment_order__contiguous ; 
 int segment_order__non_contiguous ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned int,int*,int*) ; 

__attribute__((used)) static bool hubbub1_get_dcc_compression_cap(struct hubbub *hubbub,
		const struct dc_dcc_surface_param *input,
		struct dc_surface_dcc_cap *output)
{
	struct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	struct dc *dc = hubbub1->base.ctx->dc;

	/* implement section 1.6.2.1 of DCN1_Programming_Guide.docx */
	enum dcc_control dcc_control;
	unsigned int bpe;
	enum segment_order segment_order_horz, segment_order_vert;
	bool req128_horz_wc, req128_vert_wc;

	memset(output, 0, sizeof(*output));

	if (dc->debug.disable_dcc == DCC_DISABLE)
		return false;

	if (!hubbub1->base.funcs->dcc_support_pixel_format(input->format, &bpe))
		return false;

	if (!hubbub1->base.funcs->dcc_support_swizzle(input->swizzle_mode, bpe,
			&segment_order_horz, &segment_order_vert))
		return false;

	hubbub1_det_request_size(input->surface_size.height,  input->surface_size.width,
			bpe, &req128_horz_wc, &req128_vert_wc);

	if (!req128_horz_wc && !req128_vert_wc) {
		dcc_control = dcc_control__256_256_xxx;
	} else if (input->scan == SCAN_DIRECTION_HORIZONTAL) {
		if (!req128_horz_wc)
			dcc_control = dcc_control__256_256_xxx;
		else if (segment_order_horz == segment_order__contiguous)
			dcc_control = dcc_control__128_128_xxx;
		else
			dcc_control = dcc_control__256_64_64;
	} else if (input->scan == SCAN_DIRECTION_VERTICAL) {
		if (!req128_vert_wc)
			dcc_control = dcc_control__256_256_xxx;
		else if (segment_order_vert == segment_order__contiguous)
			dcc_control = dcc_control__128_128_xxx;
		else
			dcc_control = dcc_control__256_64_64;
	} else {
		if ((req128_horz_wc &&
			segment_order_horz == segment_order__non_contiguous) ||
			(req128_vert_wc &&
			segment_order_vert == segment_order__non_contiguous))
			/* access_dir not known, must use most constraining */
			dcc_control = dcc_control__256_64_64;
		else
			/* reg128 is true for either horz and vert
			 * but segment_order is contiguous
			 */
			dcc_control = dcc_control__128_128_xxx;
	}

	if (dc->debug.disable_dcc == DCC_HALF_REQ_DISALBE &&
		dcc_control != dcc_control__256_256_xxx)
		return false;

	switch (dcc_control) {
	case dcc_control__256_256_xxx:
		output->grph.rgb.max_uncompressed_blk_size = 256;
		output->grph.rgb.max_compressed_blk_size = 256;
		output->grph.rgb.independent_64b_blks = false;
		break;
	case dcc_control__128_128_xxx:
		output->grph.rgb.max_uncompressed_blk_size = 128;
		output->grph.rgb.max_compressed_blk_size = 128;
		output->grph.rgb.independent_64b_blks = false;
		break;
	case dcc_control__256_64_64:
		output->grph.rgb.max_uncompressed_blk_size = 256;
		output->grph.rgb.max_compressed_blk_size = 64;
		output->grph.rgb.independent_64b_blks = true;
		break;
	}

	output->capable = true;
	output->const_color_support = false;

	return true;
}