#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dc_stream_state {int /*<<< orphan*/  refcount; TYPE_1__* ctx; int /*<<< orphan*/  stream_id; scalar_t__ out_transfer_func; scalar_t__ sink; } ;
struct TYPE_2__ {int /*<<< orphan*/  dc_stream_id_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dc_sink_retain (scalar_t__) ; 
 int /*<<< orphan*/  dc_transfer_func_retain (scalar_t__) ; 
 struct dc_stream_state* kmemdup (struct dc_stream_state const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

struct dc_stream_state *dc_copy_stream(const struct dc_stream_state *stream)
{
	struct dc_stream_state *new_stream;

	new_stream = kmemdup(stream, sizeof(struct dc_stream_state), GFP_KERNEL);
	if (!new_stream)
		return NULL;

	if (new_stream->sink)
		dc_sink_retain(new_stream->sink);

	if (new_stream->out_transfer_func)
		dc_transfer_func_retain(new_stream->out_transfer_func);

	new_stream->stream_id = new_stream->ctx->dc_stream_id_count;
	new_stream->ctx->dc_stream_id_count++;

	kref_init(&new_stream->refcount);

	return new_stream;
}