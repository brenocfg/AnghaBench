#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {scalar_t__ pixelclock; } ;
struct ths7303_state {int std_id; TYPE_1__ bt; } ;

/* Variables and functions */
 int /*<<< orphan*/  THS7303_FILTER_MODE_480I_576I ; 
 int /*<<< orphan*/  THS7303_FILTER_MODE_DISABLE ; 
 int V4L2_STD_ALL ; 
 int V4L2_STD_SECAM ; 
 int ths7303_setval (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct ths7303_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int ths7303_s_std_output(struct v4l2_subdev *sd, v4l2_std_id norm)
{
	struct ths7303_state *state = to_state(sd);

	if (norm & (V4L2_STD_ALL & ~V4L2_STD_SECAM)) {
		state->std_id = 1;
		state->bt.pixelclock = 0;
		return ths7303_setval(sd, THS7303_FILTER_MODE_480I_576I);
	}

	return ths7303_setval(sd, THS7303_FILTER_MODE_DISABLE);
}