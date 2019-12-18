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
struct aspeed_video {int /*<<< orphan*/  flags; scalar_t__ sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  VIDEO_STREAMING ; 
 int /*<<< orphan*/  aspeed_video_bufs_done (struct aspeed_video*,int /*<<< orphan*/ ) ; 
 int aspeed_video_start_frame (struct aspeed_video*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct aspeed_video* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int aspeed_video_start_streaming(struct vb2_queue *q,
					unsigned int count)
{
	int rc;
	struct aspeed_video *video = vb2_get_drv_priv(q);

	video->sequence = 0;

	rc = aspeed_video_start_frame(video);
	if (rc) {
		aspeed_video_bufs_done(video, VB2_BUF_STATE_QUEUED);
		return rc;
	}

	set_bit(VIDEO_STREAMING, &video->flags);
	return 0;
}