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
struct adv7842_state {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ ADV7842_MODE_SDP ; 
 int adv7842_cp_log_status (struct v4l2_subdev*) ; 
 int adv7842_sdp_log_status (struct v4l2_subdev*) ; 
 struct adv7842_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7842_log_status(struct v4l2_subdev *sd)
{
	struct adv7842_state *state = to_state(sd);

	if (state->mode == ADV7842_MODE_SDP)
		return adv7842_sdp_log_status(sd);
	return adv7842_cp_log_status(sd);
}