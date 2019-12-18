#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {TYPE_4__* stream_enc; } ;
struct pipe_ctx {TYPE_3__ stream_res; TYPE_1__* stream; } ;
struct TYPE_8__ {TYPE_2__* funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* send_immediate_sdp_message ) (TYPE_4__*,int /*<<< orphan*/  const*,unsigned int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  signal; } ;

/* Variables and functions */
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void dcn10_send_immediate_sdp_message(struct pipe_ctx *pipe_ctx,
				const uint8_t *custom_sdp_message,
				unsigned int sdp_message_size)
{
	if (dc_is_dp_signal(pipe_ctx->stream->signal)) {
		pipe_ctx->stream_res.stream_enc->funcs->send_immediate_sdp_message(
				pipe_ctx->stream_res.stream_enc,
				custom_sdp_message,
				sdp_message_size);
	}
}