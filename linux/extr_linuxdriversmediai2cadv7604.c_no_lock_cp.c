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
struct adv76xx_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  adv76xx_has_afe (struct adv76xx_state*) ; 
 int io_read (struct v4l2_subdev*,int) ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static inline bool no_lock_cp(struct v4l2_subdev *sd)
{
	struct adv76xx_state *state = to_state(sd);

	if (!adv76xx_has_afe(state))
		return false;

	/* CP has detected a non standard number of lines on the incoming
	   video compared to what it is configured to receive by s_dv_timings */
	return io_read(sd, 0x12) & 0x01;
}