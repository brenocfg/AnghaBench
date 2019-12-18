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
struct stream_encoder {int dummy; } ;
struct dcn10_stream_encoder {struct stream_encoder base; } ;
struct dc_context {int /*<<< orphan*/  dc_bios; } ;
typedef  enum engine_id { ____Placeholder_engine_id } engine_id ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dcn20_stream_encoder_construct (struct dcn10_stream_encoder*,struct dc_context*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dcn10_stream_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se_mask ; 
 int /*<<< orphan*/  se_shift ; 
 int /*<<< orphan*/ * stream_enc_regs ; 

struct stream_encoder *dcn21_stream_encoder_create(
	enum engine_id eng_id,
	struct dc_context *ctx)
{
	struct dcn10_stream_encoder *enc1 =
		kzalloc(sizeof(struct dcn10_stream_encoder), GFP_KERNEL);

	if (!enc1)
		return NULL;

	dcn20_stream_encoder_construct(enc1, ctx, ctx->dc_bios, eng_id,
					&stream_enc_regs[eng_id],
					&se_shift, &se_mask);

	return &enc1->base;
}