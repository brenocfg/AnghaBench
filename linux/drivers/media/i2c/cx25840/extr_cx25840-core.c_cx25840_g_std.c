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
struct cx25840_state {int /*<<< orphan*/  std; } ;

/* Variables and functions */
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx25840_g_std(struct v4l2_subdev *sd, v4l2_std_id *std)
{
	struct cx25840_state *state = to_state(sd);

	*std = state->std;

	return 0;
}