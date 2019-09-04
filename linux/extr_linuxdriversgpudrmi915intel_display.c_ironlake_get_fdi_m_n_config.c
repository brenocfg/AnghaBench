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
struct intel_crtc_state {int /*<<< orphan*/  fdi_m_n; int /*<<< orphan*/  cpu_transcoder; } ;
struct intel_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_cpu_transcoder_get_m_n (struct intel_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ironlake_get_fdi_m_n_config(struct intel_crtc *crtc,
					struct intel_crtc_state *pipe_config)
{
	intel_cpu_transcoder_get_m_n(crtc, pipe_config->cpu_transcoder,
				     &pipe_config->fdi_m_n, NULL);
}