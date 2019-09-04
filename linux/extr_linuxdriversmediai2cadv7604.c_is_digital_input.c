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
struct adv76xx_state {scalar_t__ selected_input; } ;

/* Variables and functions */
 scalar_t__ ADV7604_PAD_HDMI_PORT_B ; 
 scalar_t__ ADV7604_PAD_HDMI_PORT_C ; 
 scalar_t__ ADV7604_PAD_HDMI_PORT_D ; 
 scalar_t__ ADV76XX_PAD_HDMI_PORT_A ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static inline bool is_digital_input(struct v4l2_subdev *sd)
{
	struct adv76xx_state *state = to_state(sd);

	return state->selected_input == ADV76XX_PAD_HDMI_PORT_A ||
	       state->selected_input == ADV7604_PAD_HDMI_PORT_B ||
	       state->selected_input == ADV7604_PAD_HDMI_PORT_C ||
	       state->selected_input == ADV7604_PAD_HDMI_PORT_D;
}