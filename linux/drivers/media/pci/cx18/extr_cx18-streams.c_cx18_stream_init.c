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
struct cx18_videobuf_buffer {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct cx18_stream {int type; int buf_size; int bufs_per_mdl; int mdl_size; int id; int vb_bytes_per_frame; int vb_bytes_per_line; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  vbuf_q_lock; int /*<<< orphan*/  vbuf_q; int /*<<< orphan*/  vb_type; int /*<<< orphan*/  vb_lock; int /*<<< orphan*/  vb_timeout; int /*<<< orphan*/  vb_capture; int /*<<< orphan*/  out_work_order; TYPE_4__ q_idle; TYPE_4__ q_full; TYPE_4__ q_busy; TYPE_4__ q_free; int /*<<< orphan*/  waitq; int /*<<< orphan*/  buf_pool; int /*<<< orphan*/  buffers; int /*<<< orphan*/  v4l2_dev_caps; int /*<<< orphan*/  dma; int /*<<< orphan*/  handle; int /*<<< orphan*/  name; struct cx18* cx; int /*<<< orphan*/ * dvb; } ;
struct TYPE_6__ {int height; } ;
struct cx18 {int* stream_buf_size; TYPE_2__ cxhdl; int /*<<< orphan*/  serialize_lock; TYPE_1__* pci_dev; int /*<<< orphan*/ * stream_buffers; struct cx18_stream* streams; } ;
struct TYPE_7__ {int /*<<< orphan*/  caps; int /*<<< orphan*/  dma; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CX18_ENC_STREAM_TYPE_YUV ; 
 int /*<<< orphan*/  CX18_INVALID_TASK_HANDLE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_HM12 ; 
 int /*<<< orphan*/  cx18_out_work_handler ; 
 int /*<<< orphan*/  cx18_queue_init (TYPE_4__*) ; 
 TYPE_3__* cx18_stream_info ; 
 int /*<<< orphan*/  cx18_vb_timeout ; 
 int /*<<< orphan*/  cx18_videobuf_qops ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct cx18_stream*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  videobuf_queue_vmalloc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct cx18_stream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx18_stream_init(struct cx18 *cx, int type)
{
	struct cx18_stream *s = &cx->streams[type];

	memset(s, 0, sizeof(*s));

	/* initialize cx18_stream fields */
	s->dvb = NULL;
	s->cx = cx;
	s->type = type;
	s->name = cx18_stream_info[type].name;
	s->handle = CX18_INVALID_TASK_HANDLE;

	s->dma = cx18_stream_info[type].dma;
	s->v4l2_dev_caps = cx18_stream_info[type].caps;
	s->buffers = cx->stream_buffers[type];
	s->buf_size = cx->stream_buf_size[type];
	INIT_LIST_HEAD(&s->buf_pool);
	s->bufs_per_mdl = 1;
	s->mdl_size = s->buf_size * s->bufs_per_mdl;

	init_waitqueue_head(&s->waitq);
	s->id = -1;
	spin_lock_init(&s->q_free.lock);
	cx18_queue_init(&s->q_free);
	spin_lock_init(&s->q_busy.lock);
	cx18_queue_init(&s->q_busy);
	spin_lock_init(&s->q_full.lock);
	cx18_queue_init(&s->q_full);
	spin_lock_init(&s->q_idle.lock);
	cx18_queue_init(&s->q_idle);

	INIT_WORK(&s->out_work_order, cx18_out_work_handler);

	INIT_LIST_HEAD(&s->vb_capture);
	timer_setup(&s->vb_timeout, cx18_vb_timeout, 0);
	spin_lock_init(&s->vb_lock);
	if (type == CX18_ENC_STREAM_TYPE_YUV) {
		spin_lock_init(&s->vbuf_q_lock);

		s->vb_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		videobuf_queue_vmalloc_init(&s->vbuf_q, &cx18_videobuf_qops,
			&cx->pci_dev->dev, &s->vbuf_q_lock,
			V4L2_BUF_TYPE_VIDEO_CAPTURE,
			V4L2_FIELD_INTERLACED,
			sizeof(struct cx18_videobuf_buffer),
			s, &cx->serialize_lock);

		/* Assume the previous pixel default */
		s->pixelformat = V4L2_PIX_FMT_HM12;
		s->vb_bytes_per_frame = cx->cxhdl.height * 720 * 3 / 2;
		s->vb_bytes_per_line = 720;
	}
}