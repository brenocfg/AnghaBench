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
struct TYPE_3__ {TYPE_2__* dsc; } ;
struct pipe_ctx {struct pipe_ctx* next_odm_pipe; TYPE_1__ stream_res; } ;
struct dce_hwseq {int dummy; } ;
struct dc {struct dce_hwseq* hwseq; } ;
struct TYPE_4__ {int /*<<< orphan*/  inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcn20_dsc_pg_control (struct dce_hwseq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dcn20_disable_stream_gating(struct dc *dc, struct pipe_ctx *pipe_ctx)
{
#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	struct dce_hwseq *hws = dc->hwseq;

	if (pipe_ctx->stream_res.dsc) {
		struct pipe_ctx *odm_pipe = pipe_ctx->next_odm_pipe;

		dcn20_dsc_pg_control(hws, pipe_ctx->stream_res.dsc->inst, true);
		while (odm_pipe) {
			dcn20_dsc_pg_control(hws, odm_pipe->stream_res.dsc->inst, true);
			odm_pipe = odm_pipe->next_odm_pipe;
		}
	}
#endif
}