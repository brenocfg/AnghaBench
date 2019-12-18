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
struct intel_crtc_state {int /*<<< orphan*/  dp_m2_n2; int /*<<< orphan*/  dp_m_n; int /*<<< orphan*/  cpu_transcoder; scalar_t__ has_pch_encoder; } ;
struct intel_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_cpu_transcoder_get_m_n (struct intel_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_pch_transcoder_get_m_n (struct intel_crtc*,int /*<<< orphan*/ *) ; 

void intel_dp_get_m_n(struct intel_crtc *crtc,
		      struct intel_crtc_state *pipe_config)
{
	if (pipe_config->has_pch_encoder)
		intel_pch_transcoder_get_m_n(crtc, &pipe_config->dp_m_n);
	else
		intel_cpu_transcoder_get_m_n(crtc, pipe_config->cpu_transcoder,
					     &pipe_config->dp_m_n,
					     &pipe_config->dp_m2_n2);
}