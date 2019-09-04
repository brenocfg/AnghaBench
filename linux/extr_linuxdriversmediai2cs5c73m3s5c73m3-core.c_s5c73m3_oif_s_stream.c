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
struct s5c73m3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __s5c73m3_s_stream (struct s5c73m3*,struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s5c73m3* oif_sd_to_s5c73m3 (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5c73m3_oif_s_stream(struct v4l2_subdev *sd, int on)
{
	struct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	int ret;

	mutex_lock(&state->lock);
	ret = __s5c73m3_s_stream(state, sd, on);
	mutex_unlock(&state->lock);

	return ret;
}