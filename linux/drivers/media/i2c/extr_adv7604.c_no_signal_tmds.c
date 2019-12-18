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
struct adv76xx_state {int selected_input; } ;

/* Variables and functions */
 int io_read (struct v4l2_subdev*,int) ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static inline bool no_signal_tmds(struct v4l2_subdev *sd)
{
	struct adv76xx_state *state = to_state(sd);

	return !(io_read(sd, 0x6a) & (0x10 >> state->selected_input));
}