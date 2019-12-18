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
struct v4l2_dv_timings {int /*<<< orphan*/  bt; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct aspeed_video {int /*<<< orphan*/  active_timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_DV_BT_656_1120 ; 
 struct aspeed_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int aspeed_video_get_dv_timings(struct file *file, void *fh,
				       struct v4l2_dv_timings *timings)
{
	struct aspeed_video *video = video_drvdata(file);

	timings->type = V4L2_DV_BT_656_1120;
	timings->bt = video->active_timings;

	return 0;
}