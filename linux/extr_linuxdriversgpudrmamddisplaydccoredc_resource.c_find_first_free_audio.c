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
struct resource_pool {int audio_count; struct audio** audios; } ;
struct resource_context {int* is_audio_acquired; int* is_stream_enc_acquired; } ;
struct audio {int dummy; } ;
typedef  enum engine_id { ____Placeholder_engine_id } engine_id ;

/* Variables and functions */

__attribute__((used)) static struct audio *find_first_free_audio(
		struct resource_context *res_ctx,
		const struct resource_pool *pool,
		enum engine_id id)
{
	int i;
	for (i = 0; i < pool->audio_count; i++) {
		if ((res_ctx->is_audio_acquired[i] == false) && (res_ctx->is_stream_enc_acquired[i] == true)) {
			/*we have enough audio endpoint, find the matching inst*/
			if (id != i)
				continue;

			return pool->audios[i];
		}
	}
	/*not found the matching one, first come first serve*/
	for (i = 0; i < pool->audio_count; i++) {
		if (res_ctx->is_audio_acquired[i] == false) {
			return pool->audios[i];
		}
	}
	return 0;
}