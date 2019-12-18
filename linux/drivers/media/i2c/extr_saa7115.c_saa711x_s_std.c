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
struct saa711x_state {scalar_t__ radio; } ;

/* Variables and functions */
 int /*<<< orphan*/  saa711x_set_v4lstd (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa711x_s_std(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct saa711x_state *state = to_state(sd);

	state->radio = 0;
	saa711x_set_v4lstd(sd, std);
	return 0;
}