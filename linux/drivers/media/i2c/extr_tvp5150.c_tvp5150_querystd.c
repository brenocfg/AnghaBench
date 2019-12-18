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

/* Variables and functions */
 int /*<<< orphan*/  V4L2_STD_UNKNOWN ; 
 scalar_t__ query_lock (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp5150_read_std (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvp5150_querystd(struct v4l2_subdev *sd, v4l2_std_id *std_id)
{
	*std_id = query_lock(sd) ? tvp5150_read_std(sd) : V4L2_STD_UNKNOWN;

	return 0;
}