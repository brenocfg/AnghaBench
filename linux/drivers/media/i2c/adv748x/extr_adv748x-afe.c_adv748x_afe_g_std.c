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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct adv748x_afe {int /*<<< orphan*/  curr_norm; } ;

/* Variables and functions */
 struct adv748x_afe* adv748x_sd_to_afe (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv748x_afe_g_std(struct v4l2_subdev *sd, v4l2_std_id *norm)
{
	struct adv748x_afe *afe = adv748x_sd_to_afe(sd);

	*norm = afe->curr_norm;

	return 0;
}