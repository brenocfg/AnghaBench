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
struct vb2_queue {int dummy; } ;
struct aspeed_video {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  STOP_TIMEOUT ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  VIDEO_FRAME_INPRG ; 
 int /*<<< orphan*/  VIDEO_STREAMING ; 
 int /*<<< orphan*/  aspeed_video_bufs_done (struct aspeed_video*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspeed_video_get_resolution (struct aspeed_video*) ; 
 int /*<<< orphan*/  aspeed_video_init_regs (struct aspeed_video*) ; 
 int /*<<< orphan*/  aspeed_video_off (struct aspeed_video*) ; 
 int /*<<< orphan*/  aspeed_video_on (struct aspeed_video*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct aspeed_video* vb2_get_drv_priv (struct vb2_queue*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aspeed_video_stop_streaming(struct vb2_queue *q)
{
	int rc;
	struct aspeed_video *video = vb2_get_drv_priv(q);

	clear_bit(VIDEO_STREAMING, &video->flags);

	rc = wait_event_timeout(video->wait,
				!test_bit(VIDEO_FRAME_INPRG, &video->flags),
				STOP_TIMEOUT);
	if (!rc) {
		dev_dbg(video->dev, "Timed out when stopping streaming\n");

		/*
		 * Need to force stop any DMA and try and get HW into a good
		 * state for future calls to start streaming again.
		 */
		aspeed_video_off(video);
		aspeed_video_on(video);

		aspeed_video_init_regs(video);

		aspeed_video_get_resolution(video);
	}

	aspeed_video_bufs_done(video, VB2_BUF_STATE_ERROR);
}