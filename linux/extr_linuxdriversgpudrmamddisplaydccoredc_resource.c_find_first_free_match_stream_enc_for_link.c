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
struct stream_encoder {scalar_t__ id; } ;
struct resource_pool {int stream_enc_count; struct stream_encoder** stream_enc; } ;
struct resource_context {int /*<<< orphan*/ * is_stream_enc_acquired; } ;
struct dc_stream_state {int /*<<< orphan*/  signal; TYPE_1__* sink; } ;
struct dc_link {TYPE_2__* link_enc; } ;
struct TYPE_4__ {scalar_t__ preferred_engine; } ;
struct TYPE_3__ {struct dc_link* link; } ;

/* Variables and functions */
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct stream_encoder *find_first_free_match_stream_enc_for_link(
		struct resource_context *res_ctx,
		const struct resource_pool *pool,
		struct dc_stream_state *stream)
{
	int i;
	int j = -1;
	struct dc_link *link = stream->sink->link;

	for (i = 0; i < pool->stream_enc_count; i++) {
		if (!res_ctx->is_stream_enc_acquired[i] &&
				pool->stream_enc[i]) {
			/* Store first available for MST second display
			 * in daisy chain use case */
			j = i;
			if (pool->stream_enc[i]->id ==
					link->link_enc->preferred_engine)
				return pool->stream_enc[i];
		}
	}

	/*
	 * below can happen in cases when stream encoder is acquired:
	 * 1) for second MST display in chain, so preferred engine already
	 * acquired;
	 * 2) for another link, which preferred engine already acquired by any
	 * MST configuration.
	 *
	 * If signal is of DP type and preferred engine not found, return last available
	 *
	 * TODO - This is just a patch up and a generic solution is
	 * required for non DP connectors.
	 */

	if (j >= 0 && dc_is_dp_signal(stream->signal))
		return pool->stream_enc[j];

	return NULL;
}