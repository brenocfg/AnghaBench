#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ivtv_stream {int type; int buf_size; int buffers; int /*<<< orphan*/  q_io; int /*<<< orphan*/  q_predma; int /*<<< orphan*/  q_dma; int /*<<< orphan*/  q_full; int /*<<< orphan*/  q_free; int /*<<< orphan*/  sg_handle; int /*<<< orphan*/  waitq; int /*<<< orphan*/  qlock; int /*<<< orphan*/  dma; int /*<<< orphan*/  caps; int /*<<< orphan*/  name; struct ivtv* itv; } ;
struct TYPE_3__ {int* kilobytes; } ;
struct ivtv {int* stream_buf_size; TYPE_1__ options; struct ivtv_stream* streams; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; scalar_t__ pio; int /*<<< orphan*/  v4l2_caps; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DMA_UNMAPPED ; 
 int /*<<< orphan*/  PCI_DMA_NONE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_queue_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* ivtv_stream_info ; 
 int /*<<< orphan*/  memset (struct ivtv_stream*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ivtv_stream_init(struct ivtv *itv, int type)
{
	struct ivtv_stream *s = &itv->streams[type];

	/* we need to keep vdev, so restore it afterwards */
	memset(s, 0, sizeof(*s));

	/* initialize ivtv_stream fields */
	s->itv = itv;
	s->type = type;
	s->name = ivtv_stream_info[type].name;
	s->caps = ivtv_stream_info[type].v4l2_caps;

	if (ivtv_stream_info[type].pio)
		s->dma = PCI_DMA_NONE;
	else
		s->dma = ivtv_stream_info[type].dma;
	s->buf_size = itv->stream_buf_size[type];
	if (s->buf_size)
		s->buffers = (itv->options.kilobytes[type] * 1024 + s->buf_size - 1) / s->buf_size;
	spin_lock_init(&s->qlock);
	init_waitqueue_head(&s->waitq);
	s->sg_handle = IVTV_DMA_UNMAPPED;
	ivtv_queue_init(&s->q_free);
	ivtv_queue_init(&s->q_full);
	ivtv_queue_init(&s->q_dma);
	ivtv_queue_init(&s->q_predma);
	ivtv_queue_init(&s->q_io);
}