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
struct ivtv_stream {int caps; } ;
struct ivtv_open_id {size_t type; struct ivtv* itv; } ;
struct ivtv {int /*<<< orphan*/  osd_video_pbase; struct ivtv_stream* streams; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_OSD_SET_STATE ; 
 int ENOTTY ; 
 int V4L2_CAP_VIDEO_OUTPUT_OVERLAY ; 
 struct ivtv_open_id* fh2id (void*) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ivtv_overlay(struct file *file, void *fh, unsigned int on)
{
	struct ivtv_open_id *id = fh2id(fh);
	struct ivtv *itv = id->itv;
	struct ivtv_stream *s = &itv->streams[fh2id(fh)->type];

	if (!(s->caps & V4L2_CAP_VIDEO_OUTPUT_OVERLAY))
		return -ENOTTY;
	if (!itv->osd_video_pbase)
		return -ENOTTY;

	ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, on != 0);

	return 0;
}