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
struct s5p_mfc_dev {int /*<<< orphan*/  curr_ctx; } ;
struct s5p_mfc_ctx {int /*<<< orphan*/  num; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFC_DEC_RES_CHANGE ; 
 int /*<<< orphan*/  s5p_mfc_decode_one_frame_v5 (struct s5p_mfc_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_mfc_set_dec_stream_buffer_v5 (struct s5p_mfc_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_mfc_run_res_change(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;

	s5p_mfc_set_dec_stream_buffer_v5(ctx, 0, 0, 0);
	dev->curr_ctx = ctx->num;
	s5p_mfc_decode_one_frame_v5(ctx, MFC_DEC_RES_CHANGE);
}