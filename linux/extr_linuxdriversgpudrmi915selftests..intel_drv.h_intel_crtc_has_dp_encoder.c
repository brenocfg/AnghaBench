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
struct intel_crtc_state {int output_types; } ;

/* Variables and functions */
 int INTEL_OUTPUT_DP ; 
 int INTEL_OUTPUT_DP_MST ; 
 int INTEL_OUTPUT_EDP ; 

__attribute__((used)) static inline bool
intel_crtc_has_dp_encoder(const struct intel_crtc_state *crtc_state)
{
	return crtc_state->output_types &
		((1 << INTEL_OUTPUT_DP) |
		 (1 << INTEL_OUTPUT_DP_MST) |
		 (1 << INTEL_OUTPUT_EDP));
}