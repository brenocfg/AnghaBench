#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; } ;
struct v4l2_dv_timings {int /*<<< orphan*/  type; TYPE_1__ bt; } ;
struct file {int dummy; } ;
struct TYPE_4__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  sizeimage; } ;
struct aspeed_video {int /*<<< orphan*/  max_compressed_size; TYPE_2__ pix_fmt; TYPE_1__ active_timings; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  V4L2_DV_BT_656_1120 ; 
 int /*<<< orphan*/  aspeed_video_set_resolution (struct aspeed_video*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct aspeed_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int aspeed_video_set_dv_timings(struct file *file, void *fh,
				       struct v4l2_dv_timings *timings)
{
	struct aspeed_video *video = video_drvdata(file);

	if (timings->bt.width == video->active_timings.width &&
	    timings->bt.height == video->active_timings.height)
		return 0;

	if (vb2_is_busy(&video->queue))
		return -EBUSY;

	video->active_timings = timings->bt;

	aspeed_video_set_resolution(video);

	video->pix_fmt.width = timings->bt.width;
	video->pix_fmt.height = timings->bt.height;
	video->pix_fmt.sizeimage = video->max_compressed_size;

	timings->type = V4L2_DV_BT_656_1120;

	return 0;
}