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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cs5345_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int cs5345_s_routing(struct v4l2_subdev *sd,
			    u32 input, u32 output, u32 config)
{
	if ((input & 0xf) > 6) {
		v4l2_err(sd, "Invalid input %d.\n", input);
		return -EINVAL;
	}
	cs5345_write(sd, 0x09, input & 0xf);
	cs5345_write(sd, 0x05, input & 0xf0);
	return 0;
}