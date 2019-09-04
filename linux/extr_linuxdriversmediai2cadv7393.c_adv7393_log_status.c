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
struct adv7393_state {int output; scalar_t__ std; } ;

/* Variables and functions */
 struct adv7393_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,...) ; 

__attribute__((used)) static int adv7393_log_status(struct v4l2_subdev *sd)
{
	struct adv7393_state *state = to_state(sd);

	v4l2_info(sd, "Standard: %llx\n", (unsigned long long)state->std);
	v4l2_info(sd, "Output: %s\n", (state->output == 0) ? "Composite" :
			((state->output == 1) ? "Component" : "S-Video"));
	return 0;
}