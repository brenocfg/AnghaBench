#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct imgu_css_pipe {TYPE_8__** abi_buffers; int /*<<< orphan*/  qlock; TYPE_6__* queue; } ;
struct imgu_css_buffer {size_t queue; size_t queue_pos; int /*<<< orphan*/  list; int /*<<< orphan*/  state; int /*<<< orphan*/  daddr; } ;
struct imgu_css {int /*<<< orphan*/  dev; struct imgu_css_pipe* pipes; int /*<<< orphan*/  streaming; } ;
struct imgu_addr_t {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  padded_width; } ;
struct TYPE_9__ {int /*<<< orphan*/  s3a_tbl; } ;
struct TYPE_10__ {TYPE_1__ dmem; } ;
struct TYPE_11__ {TYPE_2__ data; } ;
struct TYPE_13__ {TYPE_4__ frame; TYPE_3__ s3a; } ;
struct imgu_abi_buffer {TYPE_5__ payload; } ;
typedef  int /*<<< orphan*/  imgu_addr_t ;
struct TYPE_16__ {int /*<<< orphan*/  daddr; struct imgu_abi_buffer* vaddr; } ;
struct TYPE_15__ {int ptr_ofs; int /*<<< orphan*/  qid; } ;
struct TYPE_14__ {int /*<<< orphan*/  bufs; int /*<<< orphan*/  width_pad; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_8__*) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int EPROTO ; 
 int /*<<< orphan*/  IMGU_ABI_EVENT_BUFFER_ENQUEUED (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMGU_ABI_QUEUE_EVENT_ID ; 
 int /*<<< orphan*/  IPU3_CSS_BUFFER_FAILED ; 
 int /*<<< orphan*/  IPU3_CSS_BUFFER_NEW ; 
 int /*<<< orphan*/  IPU3_CSS_BUFFER_QUEUED ; 
 size_t IPU3_CSS_QUEUES ; 
 size_t IPU3_CSS_QUEUE_OUT ; 
 size_t IPU3_CSS_QUEUE_STAT_3A ; 
 size_t IPU3_CSS_QUEUE_VF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct imgu_css_buffer*,size_t,unsigned int) ; 
 int imgu_css_queue_data (struct imgu_css*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 size_t imgu_css_queue_pos (struct imgu_css*,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_7__* imgu_css_queues ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct imgu_abi_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int imgu_css_buf_queue(struct imgu_css *css, unsigned int pipe,
		       struct imgu_css_buffer *b)
{
	struct imgu_abi_buffer *abi_buf;
	struct imgu_addr_t *buf_addr;
	u32 data;
	int r;
	struct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	if (!css->streaming)
		return -EPROTO;	/* CSS or buffer in wrong state */

	if (b->queue >= IPU3_CSS_QUEUES || !imgu_css_queues[b->queue].qid)
		return -EINVAL;

	b->queue_pos = imgu_css_queue_pos(css, imgu_css_queues[b->queue].qid,
					  pipe);

	if (b->queue_pos >= ARRAY_SIZE(css->pipes[pipe].abi_buffers[b->queue]))
		return -EIO;
	abi_buf = css->pipes[pipe].abi_buffers[b->queue][b->queue_pos].vaddr;

	/* Fill struct abi_buffer for firmware */
	memset(abi_buf, 0, sizeof(*abi_buf));

	buf_addr = (void *)abi_buf + imgu_css_queues[b->queue].ptr_ofs;
	*(imgu_addr_t *)buf_addr = b->daddr;

	if (b->queue == IPU3_CSS_QUEUE_STAT_3A)
		abi_buf->payload.s3a.data.dmem.s3a_tbl = b->daddr;

	if (b->queue == IPU3_CSS_QUEUE_OUT)
		abi_buf->payload.frame.padded_width =
				css_pipe->queue[IPU3_CSS_QUEUE_OUT].width_pad;

	if (b->queue == IPU3_CSS_QUEUE_VF)
		abi_buf->payload.frame.padded_width =
					css_pipe->queue[IPU3_CSS_QUEUE_VF].width_pad;

	spin_lock(&css_pipe->qlock);
	list_add_tail(&b->list, &css_pipe->queue[b->queue].bufs);
	spin_unlock(&css_pipe->qlock);
	b->state = IPU3_CSS_BUFFER_QUEUED;

	data = css->pipes[pipe].abi_buffers[b->queue][b->queue_pos].daddr;
	r = imgu_css_queue_data(css, imgu_css_queues[b->queue].qid,
				pipe, data);
	if (r < 0)
		goto queueing_failed;

	data = IMGU_ABI_EVENT_BUFFER_ENQUEUED(pipe,
					      imgu_css_queues[b->queue].qid);
	r = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe, data);
	if (r < 0)
		goto queueing_failed;

	dev_dbg(css->dev, "queued buffer %p to css queue %i in pipe %d\n",
		b, b->queue, pipe);

	return 0;

queueing_failed:
	b->state = (r == -EBUSY || r == -EAGAIN) ?
		IPU3_CSS_BUFFER_NEW : IPU3_CSS_BUFFER_FAILED;
	list_del(&b->list);

	return r;
}