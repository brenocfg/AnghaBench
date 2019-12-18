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
struct yuv_playback_info {int track_osd; } ;
struct v4l2_framebuffer {int flags; } ;
struct ivtv_stream {int caps; } ;
struct ivtv_open_id {size_t type; struct ivtv* itv; } ;
struct ivtv {int osd_global_alpha_state; int osd_local_alpha_state; int osd_chroma_key_state; int /*<<< orphan*/  osd_video_pbase; struct yuv_playback_info yuv_info; struct ivtv_stream* streams; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 
 int V4L2_CAP_VIDEO_OUTPUT_OVERLAY ; 
 int V4L2_FBUF_FLAG_CHROMAKEY ; 
 int V4L2_FBUF_FLAG_GLOBAL_ALPHA ; 
 int V4L2_FBUF_FLAG_LOCAL_ALPHA ; 
 int V4L2_FBUF_FLAG_LOCAL_INV_ALPHA ; 
 int V4L2_FBUF_FLAG_OVERLAY ; 
 struct ivtv_open_id* fh2id (void*) ; 
 int /*<<< orphan*/  ivtv_set_osd_alpha (struct ivtv*) ; 

__attribute__((used)) static int ivtv_s_fbuf(struct file *file, void *fh, const struct v4l2_framebuffer *fb)
{
	struct ivtv_open_id *id = fh2id(fh);
	struct ivtv *itv = id->itv;
	struct ivtv_stream *s = &itv->streams[fh2id(fh)->type];
	struct yuv_playback_info *yi = &itv->yuv_info;

	if (!(s->caps & V4L2_CAP_VIDEO_OUTPUT_OVERLAY))
		return -ENOTTY;
	if (!itv->osd_video_pbase)
		return -ENOTTY;

	itv->osd_global_alpha_state = (fb->flags & V4L2_FBUF_FLAG_GLOBAL_ALPHA) != 0;
	itv->osd_local_alpha_state =
		(fb->flags & (V4L2_FBUF_FLAG_LOCAL_ALPHA|V4L2_FBUF_FLAG_LOCAL_INV_ALPHA)) != 0;
	itv->osd_chroma_key_state = (fb->flags & V4L2_FBUF_FLAG_CHROMAKEY) != 0;
	ivtv_set_osd_alpha(itv);
	yi->track_osd = (fb->flags & V4L2_FBUF_FLAG_OVERLAY) != 0;
	return 0;
}