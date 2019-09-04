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
struct intel_crtc_state {scalar_t__ port_clock; } ;
struct dp_aud_n_m {int sample_rate; scalar_t__ clock; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dp_aud_n_m const*) ; 
 struct dp_aud_n_m const* dp_aud_n_m ; 

__attribute__((used)) static const struct dp_aud_n_m *
audio_config_dp_get_n_m(const struct intel_crtc_state *crtc_state, int rate)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dp_aud_n_m); i++) {
		if (rate == dp_aud_n_m[i].sample_rate &&
		    crtc_state->port_clock == dp_aud_n_m[i].clock)
			return &dp_aud_n_m[i];
	}

	return NULL;
}