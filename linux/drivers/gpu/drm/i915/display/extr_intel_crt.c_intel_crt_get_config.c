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
struct intel_encoder {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  crtc_clock; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ adjusted_mode; } ;
struct intel_crtc_state {int /*<<< orphan*/  port_clock; TYPE_2__ base; int /*<<< orphan*/  output_types; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_ANALOG ; 
 int /*<<< orphan*/  intel_crt_get_flags (struct intel_encoder*) ; 

__attribute__((used)) static void intel_crt_get_config(struct intel_encoder *encoder,
				 struct intel_crtc_state *pipe_config)
{
	pipe_config->output_types |= BIT(INTEL_OUTPUT_ANALOG);

	pipe_config->base.adjusted_mode.flags |= intel_crt_get_flags(encoder);

	pipe_config->base.adjusted_mode.crtc_clock = pipe_config->port_clock;
}