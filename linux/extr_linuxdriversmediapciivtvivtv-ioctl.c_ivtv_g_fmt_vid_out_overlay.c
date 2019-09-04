#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ left; scalar_t__ top; } ;
struct v4l2_window {TYPE_2__ w; int /*<<< orphan*/ * bitmap; scalar_t__ clipcount; int /*<<< orphan*/ * clips; int /*<<< orphan*/  field; int /*<<< orphan*/  global_alpha; int /*<<< orphan*/  chromakey; } ;
struct TYPE_5__ {struct v4l2_window win; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct ivtv_stream {int caps; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ivtv {TYPE_3__ osd_rect; int /*<<< orphan*/  osd_global_alpha; int /*<<< orphan*/  osd_chroma_key; int /*<<< orphan*/  osd_video_pbase; struct ivtv_stream* streams; } ;
struct file {int dummy; } ;
struct TYPE_8__ {size_t type; struct ivtv* itv; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_CAP_VIDEO_OUTPUT_OVERLAY ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 TYPE_4__* fh2id (void*) ; 

__attribute__((used)) static int ivtv_g_fmt_vid_out_overlay(struct file *file, void *fh, struct v4l2_format *fmt)
{
	struct ivtv *itv = fh2id(fh)->itv;
	struct ivtv_stream *s = &itv->streams[fh2id(fh)->type];
	struct v4l2_window *winfmt = &fmt->fmt.win;

	if (!(s->caps & V4L2_CAP_VIDEO_OUTPUT_OVERLAY))
		return -EINVAL;
	if (!itv->osd_video_pbase)
		return -EINVAL;
	winfmt->chromakey = itv->osd_chroma_key;
	winfmt->global_alpha = itv->osd_global_alpha;
	winfmt->field = V4L2_FIELD_INTERLACED;
	winfmt->clips = NULL;
	winfmt->clipcount = 0;
	winfmt->bitmap = NULL;
	winfmt->w.top = winfmt->w.left = 0;
	winfmt->w.width = itv->osd_rect.width;
	winfmt->w.height = itv->osd_rect.height;
	return 0;
}