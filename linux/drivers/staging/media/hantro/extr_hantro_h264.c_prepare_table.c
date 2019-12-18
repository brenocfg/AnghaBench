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
struct v4l2_h264_dpb_entry {int /*<<< orphan*/  bottom_field_order_cnt; int /*<<< orphan*/  top_field_order_cnt; } ;
struct v4l2_ctrl_h264_decode_params {int /*<<< orphan*/  bottom_field_order_cnt; int /*<<< orphan*/  top_field_order_cnt; } ;
struct hantro_h264_dec_priv_tbl {int /*<<< orphan*/ * poc; } ;
struct hantro_h264_dec_ctrls {struct v4l2_ctrl_h264_decode_params* decode; } ;
struct TYPE_3__ {struct hantro_h264_dec_priv_tbl* cpu; } ;
struct TYPE_4__ {struct v4l2_h264_dpb_entry* dpb; TYPE_1__ priv; struct hantro_h264_dec_ctrls ctrls; } ;
struct hantro_ctx {TYPE_2__ h264_dec; } ;

/* Variables and functions */
 int HANTRO_H264_DPB_SIZE ; 
 int /*<<< orphan*/  reorder_scaling_list (struct hantro_ctx*) ; 

__attribute__((used)) static void prepare_table(struct hantro_ctx *ctx)
{
	const struct hantro_h264_dec_ctrls *ctrls = &ctx->h264_dec.ctrls;
	const struct v4l2_ctrl_h264_decode_params *dec_param = ctrls->decode;
	struct hantro_h264_dec_priv_tbl *tbl = ctx->h264_dec.priv.cpu;
	const struct v4l2_h264_dpb_entry *dpb = ctx->h264_dec.dpb;
	int i;

	for (i = 0; i < HANTRO_H264_DPB_SIZE; ++i) {
		tbl->poc[i * 2] = dpb[i].top_field_order_cnt;
		tbl->poc[i * 2 + 1] = dpb[i].bottom_field_order_cnt;
	}

	tbl->poc[32] = dec_param->top_field_order_cnt;
	tbl->poc[33] = dec_param->bottom_field_order_cnt;

	reorder_scaling_list(ctx);
}