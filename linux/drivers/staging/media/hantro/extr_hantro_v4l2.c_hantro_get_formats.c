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
struct hantro_fmt {int dummy; } ;
struct hantro_ctx {TYPE_1__* dev; } ;
struct TYPE_4__ {unsigned int num_enc_fmts; unsigned int num_dec_fmts; struct hantro_fmt* dec_fmts; struct hantro_fmt* enc_fmts; } ;
struct TYPE_3__ {TYPE_2__* variant; } ;

/* Variables and functions */
 scalar_t__ hantro_is_encoder_ctx (struct hantro_ctx const*) ; 

__attribute__((used)) static const struct hantro_fmt *
hantro_get_formats(const struct hantro_ctx *ctx, unsigned int *num_fmts)
{
	const struct hantro_fmt *formats;

	if (hantro_is_encoder_ctx(ctx)) {
		formats = ctx->dev->variant->enc_fmts;
		*num_fmts = ctx->dev->variant->num_enc_fmts;
	} else {
		formats = ctx->dev->variant->dec_fmts;
		*num_fmts = ctx->dev->variant->num_dec_fmts;
	}

	return formats;
}