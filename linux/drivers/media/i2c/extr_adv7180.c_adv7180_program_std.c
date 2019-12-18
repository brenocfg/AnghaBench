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
struct adv7180_state {int /*<<< orphan*/  curr_norm; } ;

/* Variables and functions */
 int adv7180_set_video_standard (struct adv7180_state*,int) ; 
 int v4l2_std_to_adv7180 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv7180_program_std(struct adv7180_state *state)
{
	int ret;

	ret = v4l2_std_to_adv7180(state->curr_norm);
	if (ret < 0)
		return ret;

	ret = adv7180_set_video_standard(state, ret);
	if (ret < 0)
		return ret;
	return 0;
}