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
struct videobuf_queue {int dummy; } ;
struct cx18_stream {int vb_type; struct videobuf_queue vbuf_q; } ;
struct cx18_open_id {size_t type; struct cx18* cx; } ;
struct cx18 {struct cx18_stream* streams; } ;

/* Variables and functions */
#define  V4L2_BUF_TYPE_VBI_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 128 

__attribute__((used)) static struct videobuf_queue *cx18_vb_queue(struct cx18_open_id *id)
{
	struct videobuf_queue *q = NULL;
	struct cx18 *cx = id->cx;
	struct cx18_stream *s = &cx->streams[id->type];

	switch (s->vb_type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		q = &s->vbuf_q;
		break;
	case V4L2_BUF_TYPE_VBI_CAPTURE:
		break;
	default:
		break;
	}
	return q;
}