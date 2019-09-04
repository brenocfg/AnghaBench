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
struct dc_stream_state {int /*<<< orphan*/ * out_transfer_func; int /*<<< orphan*/  sink; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_sink_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_transfer_func_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destruct(struct dc_stream_state *stream)
{
	dc_sink_release(stream->sink);
	if (stream->out_transfer_func != NULL) {
		dc_transfer_func_release(stream->out_transfer_func);
		stream->out_transfer_func = NULL;
	}
}