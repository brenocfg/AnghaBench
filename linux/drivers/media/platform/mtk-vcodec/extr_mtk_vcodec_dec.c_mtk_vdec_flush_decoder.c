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
struct mtk_vcodec_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_display_buffer (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  clean_free_buffer (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*,int) ; 
 int vdec_if_decode (struct mtk_vcodec_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void mtk_vdec_flush_decoder(struct mtk_vcodec_ctx *ctx)
{
	bool res_chg;
	int ret = 0;

	ret = vdec_if_decode(ctx, NULL, NULL, &res_chg);
	if (ret)
		mtk_v4l2_err("DecodeFinal failed, ret=%d", ret);

	clean_display_buffer(ctx);
	clean_free_buffer(ctx);
}