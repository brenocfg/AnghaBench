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
typedef  int /*<<< orphan*/  u32 ;
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 TYPE_1__* enc_to_intel_lspcon (int /*<<< orphan*/ *) ; 

u32 lspcon_infoframes_enabled(struct intel_encoder *encoder,
			      const struct intel_crtc_state *pipe_config)
{
	/* FIXME actually read this from the hw */
	return enc_to_intel_lspcon(&encoder->base)->active;
}