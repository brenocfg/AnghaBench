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
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct aspeed_video_buffer {int /*<<< orphan*/  link; } ;
struct aspeed_video {int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_FRAME_INPRG ; 
 int /*<<< orphan*/  VIDEO_STREAMING ; 
 int /*<<< orphan*/  aspeed_video_start_frame (struct aspeed_video*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct aspeed_video_buffer* to_aspeed_video_buffer (struct vb2_v4l2_buffer*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct aspeed_video* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aspeed_video_buf_queue(struct vb2_buffer *vb)
{
	bool empty;
	struct aspeed_video *video = vb2_get_drv_priv(vb->vb2_queue);
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct aspeed_video_buffer *avb = to_aspeed_video_buffer(vbuf);
	unsigned long flags;

	spin_lock_irqsave(&video->lock, flags);
	empty = list_empty(&video->buffers);
	list_add_tail(&avb->link, &video->buffers);
	spin_unlock_irqrestore(&video->lock, flags);

	if (test_bit(VIDEO_STREAMING, &video->flags) &&
	    !test_bit(VIDEO_FRAME_INPRG, &video->flags) && empty)
		aspeed_video_start_frame(video);
}