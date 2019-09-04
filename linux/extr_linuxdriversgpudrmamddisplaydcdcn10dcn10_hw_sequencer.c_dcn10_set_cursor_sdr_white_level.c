#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {TYPE_5__* dpp; } ;
struct pipe_ctx {TYPE_4__ plane_res; TYPE_2__* stream; } ;
struct fixed31_32 {int dummy; } ;
struct dpp_cursor_attributes {int scale; scalar_t__ bias; int /*<<< orphan*/  member_0; } ;
struct custom_float_format {int exponenta_bits; int mantissa_bits; int sign; } ;
struct TYPE_10__ {TYPE_3__* funcs; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_optional_cursor_attributes ) (TYPE_5__*,struct dpp_cursor_attributes*) ;} ;
struct TYPE_6__ {int sdr_white_level; } ;
struct TYPE_7__ {TYPE_1__ cursor_attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  convert_to_custom_float_format (struct fixed31_32,struct custom_float_format*,int*) ; 
 struct fixed31_32 dc_fixpt_from_fraction (int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,struct dpp_cursor_attributes*) ; 

__attribute__((used)) static void dcn10_set_cursor_sdr_white_level(struct pipe_ctx *pipe_ctx)
{
	uint32_t sdr_white_level = pipe_ctx->stream->cursor_attributes.sdr_white_level;
	struct fixed31_32 multiplier;
	struct dpp_cursor_attributes opt_attr = { 0 };
	uint32_t hw_scale = 0x3c00; // 1.0 default multiplier
	struct custom_float_format fmt;

	if (!pipe_ctx->plane_res.dpp->funcs->set_optional_cursor_attributes)
		return;

	fmt.exponenta_bits = 5;
	fmt.mantissa_bits = 10;
	fmt.sign = true;

	if (sdr_white_level > 80) {
		multiplier = dc_fixpt_from_fraction(sdr_white_level, 80);
		convert_to_custom_float_format(multiplier, &fmt, &hw_scale);
	}

	opt_attr.scale = hw_scale;
	opt_attr.bias = 0;

	pipe_ctx->plane_res.dpp->funcs->set_optional_cursor_attributes(
			pipe_ctx->plane_res.dpp, &opt_attr);
}