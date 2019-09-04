#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  global_alpha; int /*<<< orphan*/  chromakey; } ;
struct TYPE_5__ {TYPE_1__ win; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct ivtv_stream {int caps; } ;
struct ivtv {int /*<<< orphan*/  osd_video_pbase; struct ivtv_stream* streams; } ;
struct file {int dummy; } ;
struct TYPE_6__ {size_t type; struct ivtv* itv; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_CAP_VIDEO_OUTPUT_OVERLAY ; 
 TYPE_3__* fh2id (void*) ; 
 int /*<<< orphan*/  ivtv_g_fmt_vid_out_overlay (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int ivtv_try_fmt_vid_out_overlay(struct file *file, void *fh, struct v4l2_format *fmt)
{
	struct ivtv *itv = fh2id(fh)->itv;
	struct ivtv_stream *s = &itv->streams[fh2id(fh)->type];
	u32 chromakey = fmt->fmt.win.chromakey;
	u8 global_alpha = fmt->fmt.win.global_alpha;

	if (!(s->caps & V4L2_CAP_VIDEO_OUTPUT_OVERLAY))
		return -EINVAL;
	if (!itv->osd_video_pbase)
		return -EINVAL;
	ivtv_g_fmt_vid_out_overlay(file, fh, fmt);
	fmt->fmt.win.chromakey = chromakey;
	fmt->fmt.win.global_alpha = global_alpha;
	return 0;
}