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
struct v4l2_subdev {int dummy; } ;
struct v4l2_dv_timings_cap {int dummy; } ;
struct adv76xx_state {int selected_input; } ;

/* Variables and functions */
#define  ADV7604_PAD_HDMI_PORT_B 133 
#define  ADV7604_PAD_HDMI_PORT_C 132 
#define  ADV7604_PAD_HDMI_PORT_D 131 
#define  ADV7604_PAD_VGA_COMP 130 
#define  ADV7604_PAD_VGA_RGB 129 
#define  ADV76XX_PAD_HDMI_PORT_A 128 
 struct v4l2_dv_timings_cap const adv7604_timings_cap_analog ; 
 struct v4l2_dv_timings_cap const adv76xx_timings_cap_digital ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static const struct v4l2_dv_timings_cap *
adv76xx_get_dv_timings_cap(struct v4l2_subdev *sd, int pad)
{
	if (pad == -1) {
		struct adv76xx_state *state = to_state(sd);

		pad = state->selected_input;
	}

	switch (pad) {
	case ADV76XX_PAD_HDMI_PORT_A:
	case ADV7604_PAD_HDMI_PORT_B:
	case ADV7604_PAD_HDMI_PORT_C:
	case ADV7604_PAD_HDMI_PORT_D:
		return &adv76xx_timings_cap_digital;

	case ADV7604_PAD_VGA_RGB:
	case ADV7604_PAD_VGA_COMP:
	default:
		return &adv7604_timings_cap_analog;
	}
}