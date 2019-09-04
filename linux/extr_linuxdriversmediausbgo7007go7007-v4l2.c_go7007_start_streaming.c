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
struct vb2_queue {int streaming; } ;
struct go7007 {scalar_t__ board_id; int /*<<< orphan*/  mpeg_video_aspect_ratio; int /*<<< orphan*/  mpeg_video_bitrate; int /*<<< orphan*/  mpeg_video_gop_closure; int /*<<< orphan*/  mpeg_video_gop_size; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  hw_lock; scalar_t__ modet_event_status; int /*<<< orphan*/ * active_buf; scalar_t__ next_seq; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ GO7007_BOARDID_ADS_USBAV_709 ; 
 int /*<<< orphan*/  call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ go7007_start_encoder (struct go7007*) ; 
 int /*<<< orphan*/  go7007_write_addr (struct go7007*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  set_formatting (struct go7007*) ; 
 int /*<<< orphan*/  v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 
 struct go7007* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int go7007_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct go7007 *go = vb2_get_drv_priv(q);
	int ret;

	set_formatting(go);
	mutex_lock(&go->hw_lock);
	go->next_seq = 0;
	go->active_buf = NULL;
	go->modet_event_status = 0;
	q->streaming = 1;
	if (go7007_start_encoder(go) < 0)
		ret = -EIO;
	else
		ret = 0;
	mutex_unlock(&go->hw_lock);
	if (ret) {
		q->streaming = 0;
		return ret;
	}
	call_all(&go->v4l2_dev, video, s_stream, 1);
	v4l2_ctrl_grab(go->mpeg_video_gop_size, true);
	v4l2_ctrl_grab(go->mpeg_video_gop_closure, true);
	v4l2_ctrl_grab(go->mpeg_video_bitrate, true);
	v4l2_ctrl_grab(go->mpeg_video_aspect_ratio, true);
	/* Turn on Capture LED */
	if (go->board_id == GO7007_BOARDID_ADS_USBAV_709)
		go7007_write_addr(go, 0x3c82, 0x0005);
	return ret;
}