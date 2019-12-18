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
struct intel_crtc_state {int /*<<< orphan*/  csc_mode; int /*<<< orphan*/  gamma_mode; } ;

/* Variables and functions */
 int check_luts (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  icl_csc_mode (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  icl_gamma_mode (struct intel_crtc_state*) ; 

__attribute__((used)) static int icl_color_check(struct intel_crtc_state *crtc_state)
{
	int ret;

	ret = check_luts(crtc_state);
	if (ret)
		return ret;

	crtc_state->gamma_mode = icl_gamma_mode(crtc_state);

	crtc_state->csc_mode = icl_csc_mode(crtc_state);

	return 0;
}