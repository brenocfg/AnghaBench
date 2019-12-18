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
struct vb2_queue {scalar_t__ streaming; } ;
struct go7007 {scalar_t__ board_id; int /*<<< orphan*/  mpeg_video_aspect_ratio; int /*<<< orphan*/  mpeg_video_bitrate; int /*<<< orphan*/  mpeg_video_gop_closure; int /*<<< orphan*/  mpeg_video_gop_size; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  vidq_active; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  hw_lock; } ;

/* Variables and functions */
 scalar_t__ GO7007_BOARDID_ADS_USBAV_709 ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  go7007_reset_encoder (struct go7007*) ; 
 int /*<<< orphan*/  go7007_stream_stop (struct go7007*) ; 
 int /*<<< orphan*/  go7007_write_addr (struct go7007*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 
 struct go7007* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static void go7007_stop_streaming(struct vb2_queue *q)
{
	struct go7007 *go = vb2_get_drv_priv(q);
	unsigned long flags;

	q->streaming = 0;
	go7007_stream_stop(go);
	mutex_lock(&go->hw_lock);
	go7007_reset_encoder(go);
	mutex_unlock(&go->hw_lock);
	call_all(&go->v4l2_dev, video, s_stream, 0);

	spin_lock_irqsave(&go->spinlock, flags);
	INIT_LIST_HEAD(&go->vidq_active);
	spin_unlock_irqrestore(&go->spinlock, flags);
	v4l2_ctrl_grab(go->mpeg_video_gop_size, false);
	v4l2_ctrl_grab(go->mpeg_video_gop_closure, false);
	v4l2_ctrl_grab(go->mpeg_video_bitrate, false);
	v4l2_ctrl_grab(go->mpeg_video_aspect_ratio, false);
	/* Turn on Capture LED */
	if (go->board_id == GO7007_BOARDID_ADS_USBAV_709)
		go7007_write_addr(go, 0x3c82, 0x000d);
}