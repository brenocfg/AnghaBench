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
struct m52790_state {int input; int output; } ;

/* Variables and functions */
 struct m52790_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int m52790_log_status(struct v4l2_subdev *sd)
{
	struct m52790_state *state = to_state(sd);

	v4l2_info(sd, "Switch 1: %02x\n",
			(state->input | state->output) & 0xff);
	v4l2_info(sd, "Switch 2: %02x\n",
			(state->input | state->output) >> 8);
	return 0;
}