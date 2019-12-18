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
struct TYPE_3__ {int crtc_clock; } ;
struct TYPE_4__ {TYPE_1__ adjusted_mode; } ;
struct intel_crtc_state {int port_clock; int pipe_bpp; scalar_t__ output_format; int pixel_multiplier; TYPE_2__ base; scalar_t__ has_hdmi_sink; int /*<<< orphan*/  dp_m_n; int /*<<< orphan*/  fdi_m_n; scalar_t__ has_pch_encoder; } ;

/* Variables and functions */
 scalar_t__ INTEL_OUTPUT_FORMAT_YCBCR420 ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 int intel_dotclock_calculate (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ddi_dotclock_get(struct intel_crtc_state *pipe_config)
{
	int dotclock;

	if (pipe_config->has_pch_encoder)
		dotclock = intel_dotclock_calculate(pipe_config->port_clock,
						    &pipe_config->fdi_m_n);
	else if (intel_crtc_has_dp_encoder(pipe_config))
		dotclock = intel_dotclock_calculate(pipe_config->port_clock,
						    &pipe_config->dp_m_n);
	else if (pipe_config->has_hdmi_sink && pipe_config->pipe_bpp > 24)
		dotclock = pipe_config->port_clock * 24 / pipe_config->pipe_bpp;
	else
		dotclock = pipe_config->port_clock;

	if (pipe_config->output_format == INTEL_OUTPUT_FORMAT_YCBCR420 &&
	    !intel_crtc_has_dp_encoder(pipe_config))
		dotclock *= 2;

	if (pipe_config->pixel_multiplier)
		dotclock /= pipe_config->pixel_multiplier;

	pipe_config->base.adjusted_mode.crtc_clock = dotclock;
}