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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct adv748x_state {int /*<<< orphan*/  mutex; } ;
struct adv748x_afe {int dummy; } ;

/* Variables and functions */
 int adv748x_afe_status (struct adv748x_afe*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct adv748x_state* adv748x_afe_to_state (struct adv748x_afe*) ; 
 struct adv748x_afe* adv748x_sd_to_afe (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adv748x_afe_g_input_status(struct v4l2_subdev *sd, u32 *status)
{
	struct adv748x_afe *afe = adv748x_sd_to_afe(sd);
	struct adv748x_state *state = adv748x_afe_to_state(afe);
	int ret;

	mutex_lock(&state->mutex);

	ret = adv748x_afe_status(afe, status, NULL);

	mutex_unlock(&state->mutex);

	return ret;
}