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
struct TYPE_2__ {scalar_t__ virt; } ;
struct aspeed_video {scalar_t__ yuv420; TYPE_1__ jpeg; } ;

/* Variables and functions */
 int /*<<< orphan*/  VE_SEQ_CTRL ; 
 int /*<<< orphan*/  VE_SEQ_CTRL_YUV420 ; 
 int /*<<< orphan*/  aspeed_video_init_jpeg_table (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  aspeed_video_update (struct aspeed_video*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aspeed_video_update_subsampling(struct aspeed_video *video)
{
	if (video->jpeg.virt)
		aspeed_video_init_jpeg_table(video->jpeg.virt, video->yuv420);

	if (video->yuv420)
		aspeed_video_update(video, VE_SEQ_CTRL, 0, VE_SEQ_CTRL_YUV420);
	else
		aspeed_video_update(video, VE_SEQ_CTRL, VE_SEQ_CTRL_YUV420, 0);
}