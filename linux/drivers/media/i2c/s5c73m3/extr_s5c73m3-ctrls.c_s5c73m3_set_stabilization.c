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
struct s5c73m3 {struct v4l2_subdev sensor_sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_FRAME_RATE ; 
 int /*<<< orphan*/  COMM_FRAME_RATE_ANTI_SHAKE ; 
 int /*<<< orphan*/  COMM_FRAME_RATE_AUTO_SET ; 
 int /*<<< orphan*/  s5c73m3_dbg ; 
 int s5c73m3_isp_command (struct s5c73m3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int s5c73m3_set_stabilization(struct s5c73m3 *state, int val)
{
	struct v4l2_subdev *sd = &state->sensor_sd;

	v4l2_dbg(1, s5c73m3_dbg, sd, "Image stabilization: %d\n", val);

	return s5c73m3_isp_command(state, COMM_FRAME_RATE, val ?
			COMM_FRAME_RATE_ANTI_SHAKE : COMM_FRAME_RATE_AUTO_SET);
}