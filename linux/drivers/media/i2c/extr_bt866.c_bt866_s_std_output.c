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
typedef  int v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_STD_NTSC ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,unsigned long long) ; 

__attribute__((used)) static int bt866_s_std_output(struct v4l2_subdev *sd, v4l2_std_id std)
{
	v4l2_dbg(1, debug, sd, "set norm %llx\n", (unsigned long long)std);

	/* Only PAL supported by this driver at the moment! */
	if (!(std & V4L2_STD_NTSC))
		return -EINVAL;
	return 0;
}