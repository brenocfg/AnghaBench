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
struct resource_straps {int /*<<< orphan*/  member_0; } ;
struct resource_pool {size_t audio_count; size_t stream_enc_count; int /*<<< orphan*/ ** stream_enc; struct audio** audios; int /*<<< orphan*/  audio_support; struct resource_caps* res_cap; } ;
struct resource_create_funcs {int /*<<< orphan*/  (* create_hwseq ) (struct dc_context*) ;int /*<<< orphan*/ * (* create_stream_encoder ) (int,struct dc_context*) ;struct audio* (* create_audio ) (struct dc_context*,int) ;int /*<<< orphan*/  (* read_dce_straps ) (struct dc_context*,struct resource_straps*) ;} ;
struct resource_caps {unsigned int num_audio; int num_stream_encoder; } ;
struct dc_context {int /*<<< orphan*/  dc_bios; } ;
struct TYPE_4__ {int dynamic_audio; } ;
struct dc {int /*<<< orphan*/  hwseq; TYPE_2__ caps; struct dc_context* ctx; } ;
struct audio {TYPE_1__* funcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy ) (struct audio**) ;int /*<<< orphan*/  (* endpoint_valid ) (struct audio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ERR (char*) ; 
 int /*<<< orphan*/  stub1 (struct dc_context*,struct resource_straps*) ; 
 struct audio* stub2 (struct dc_context*,int) ; 
 int /*<<< orphan*/  stub3 (struct audio*) ; 
 int /*<<< orphan*/  stub4 (struct audio**) ; 
 int /*<<< orphan*/ * stub5 (int,struct dc_context*) ; 
 int /*<<< orphan*/  stub6 (struct dc_context*) ; 
 int /*<<< orphan*/  update_num_audio (struct resource_straps*,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * virtual_stream_encoder_create (struct dc_context*,int /*<<< orphan*/ ) ; 

bool resource_construct(
	unsigned int num_virtual_links,
	struct dc  *dc,
	struct resource_pool *pool,
	const struct resource_create_funcs *create_funcs)
{
	struct dc_context *ctx = dc->ctx;
	const struct resource_caps *caps = pool->res_cap;
	int i;
	unsigned int num_audio = caps->num_audio;
	struct resource_straps straps = {0};

	if (create_funcs->read_dce_straps)
		create_funcs->read_dce_straps(dc->ctx, &straps);

	pool->audio_count = 0;
	if (create_funcs->create_audio) {
		/* find the total number of streams available via the
		 * AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT
		 * registers (one for each pin) starting from pin 1
		 * up to the max number of audio pins.
		 * We stop on the first pin where
		 * PORT_CONNECTIVITY == 1 (as instructed by HW team).
		 */
		update_num_audio(&straps, &num_audio, &pool->audio_support);
		for (i = 0; i < caps->num_audio; i++) {
			struct audio *aud = create_funcs->create_audio(ctx, i);

			if (aud == NULL) {
				DC_ERR("DC: failed to create audio!\n");
				return false;
			}
			if (!aud->funcs->endpoint_valid(aud)) {
				aud->funcs->destroy(&aud);
				break;
			}
			pool->audios[i] = aud;
			pool->audio_count++;
		}
	}

	pool->stream_enc_count = 0;
	if (create_funcs->create_stream_encoder) {
		for (i = 0; i < caps->num_stream_encoder; i++) {
			pool->stream_enc[i] = create_funcs->create_stream_encoder(i, ctx);
			if (pool->stream_enc[i] == NULL)
				DC_ERR("DC: failed to create stream_encoder!\n");
			pool->stream_enc_count++;
		}
	}

	dc->caps.dynamic_audio = false;
	if (pool->audio_count < pool->stream_enc_count) {
		dc->caps.dynamic_audio = true;
	}
	for (i = 0; i < num_virtual_links; i++) {
		pool->stream_enc[pool->stream_enc_count] =
			virtual_stream_encoder_create(
					ctx, ctx->dc_bios);
		if (pool->stream_enc[pool->stream_enc_count] == NULL) {
			DC_ERR("DC: failed to create stream_encoder!\n");
			return false;
		}
		pool->stream_enc_count++;
	}

	dc->hwseq = create_funcs->create_hwseq(ctx);

	return true;
}