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
struct intel_crtc_scaler_state {TYPE_2__* scalers; } ;
struct intel_crtc {int num_scalers; TYPE_1__* config; } ;
struct TYPE_4__ {int /*<<< orphan*/  in_use; } ;
struct TYPE_3__ {struct intel_crtc_scaler_state scaler_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  skl_detach_scaler (struct intel_crtc*,int) ; 

__attribute__((used)) static void skl_detach_scalers(struct intel_crtc *intel_crtc)
{
	struct intel_crtc_scaler_state *scaler_state;
	int i;

	scaler_state = &intel_crtc->config->scaler_state;

	/* loop through and disable scalers that aren't in use */
	for (i = 0; i < intel_crtc->num_scalers; i++) {
		if (!scaler_state->scalers[i].in_use)
			skl_detach_scaler(intel_crtc, i);
	}
}