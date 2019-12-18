#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pipe_ctx {TYPE_3__* stream; } ;
struct dc_state {int dummy; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_6__ {int signal; TYPE_2__* link; } ;
struct TYPE_4__ {int link_active; } ;
struct TYPE_5__ {TYPE_1__ link_status; } ;

/* Variables and functions */
 int DC_ERROR_UNEXPECTED ; 
 int DC_OK ; 
#define  SIGNAL_TYPE_DISPLAY_PORT 135 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 134 
#define  SIGNAL_TYPE_DVI_DUAL_LINK 133 
#define  SIGNAL_TYPE_DVI_SINGLE_LINK 132 
#define  SIGNAL_TYPE_EDP 131 
#define  SIGNAL_TYPE_HDMI_TYPE_A 130 
#define  SIGNAL_TYPE_LVDS 129 
#define  SIGNAL_TYPE_VIRTUAL 128 
 int enable_link_dp (struct dc_state*,struct pipe_ctx*) ; 
 int enable_link_dp_mst (struct dc_state*,struct pipe_ctx*) ; 
 int enable_link_edp (struct dc_state*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  enable_link_hdmi (struct pipe_ctx*) ; 
 int /*<<< orphan*/  enable_link_lvds (struct pipe_ctx*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static enum dc_status enable_link(
		struct dc_state *state,
		struct pipe_ctx *pipe_ctx)
{
	enum dc_status status = DC_ERROR_UNEXPECTED;
	switch (pipe_ctx->stream->signal) {
	case SIGNAL_TYPE_DISPLAY_PORT:
		status = enable_link_dp(state, pipe_ctx);
		break;
	case SIGNAL_TYPE_EDP:
		status = enable_link_edp(state, pipe_ctx);
		break;
	case SIGNAL_TYPE_DISPLAY_PORT_MST:
		status = enable_link_dp_mst(state, pipe_ctx);
		msleep(200);
		break;
	case SIGNAL_TYPE_DVI_SINGLE_LINK:
	case SIGNAL_TYPE_DVI_DUAL_LINK:
	case SIGNAL_TYPE_HDMI_TYPE_A:
		enable_link_hdmi(pipe_ctx);
		status = DC_OK;
		break;
	case SIGNAL_TYPE_LVDS:
		enable_link_lvds(pipe_ctx);
		status = DC_OK;
		break;
	case SIGNAL_TYPE_VIRTUAL:
		status = DC_OK;
		break;
	default:
		break;
	}

	if (status == DC_OK)
		pipe_ctx->stream->link->link_status.link_active = true;

	return status;
}