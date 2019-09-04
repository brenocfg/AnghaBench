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
typedef  enum intel_output_type { ____Placeholder_intel_output_type } intel_output_type ;

/* Variables and functions */

__attribute__((used)) static inline bool
intel_crtc_has_type(const struct intel_crtc_state *crtc_state,
		    enum intel_output_type type)
{
	return crtc_state->output_types & (1 << type);
}