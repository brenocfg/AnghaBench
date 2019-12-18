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
typedef  int /*<<< orphan*/  ulong ;
struct aspeed_video {int /*<<< orphan*/  res_work; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  VIDEO_FRAME_INPRG ; 
 int /*<<< orphan*/  VIDEO_RES_CHANGE ; 
 int /*<<< orphan*/  aspeed_video_bufs_done (struct aspeed_video*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspeed_video_off (struct aspeed_video*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aspeed_video_irq_res_change(struct aspeed_video *video, ulong delay)
{
	dev_dbg(video->dev, "Resolution changed; resetting\n");

	set_bit(VIDEO_RES_CHANGE, &video->flags);
	clear_bit(VIDEO_FRAME_INPRG, &video->flags);

	aspeed_video_off(video);
	aspeed_video_bufs_done(video, VB2_BUF_STATE_ERROR);

	schedule_delayed_work(&video->res_work, delay);
}