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
struct timing_generator {int dummy; } ;
typedef  enum crtc_state { ____Placeholder_crtc_state } crtc_state ;

/* Variables and functions */
#define  CRTC_STATE_VACTIVE 129 
#define  CRTC_STATE_VBLANK 128 
 int /*<<< orphan*/  dce120_timing_generator_wait_for_vactive (struct timing_generator*) ; 
 int /*<<< orphan*/  dce120_timing_generator_wait_for_vblank (struct timing_generator*) ; 

void dce120_tg_wait_for_state(struct timing_generator *tg,
	enum crtc_state state)
{
	switch (state) {
	case CRTC_STATE_VBLANK:
		dce120_timing_generator_wait_for_vblank(tg);
		break;

	case CRTC_STATE_VACTIVE:
		dce120_timing_generator_wait_for_vactive(tg);
		break;

	default:
		break;
	}
}