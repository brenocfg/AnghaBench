#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct via_camera {int n_cap_bufs; int /*<<< orphan*/  lock; int /*<<< orphan*/  sequence; int /*<<< orphan*/ * cb_offsets; } ;
struct TYPE_5__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_4__ {TYPE_2__ vb2_buf; int /*<<< orphan*/  field; scalar_t__ sequence; } ;
struct via_buffer {TYPE_1__ vbuf; int /*<<< orphan*/  queue; } ;
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int VCR_IC_ACTBUF ; 
 int /*<<< orphan*/  VCR_INTCTRL ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct sg_table* vb2_dma_sg_plane_desc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct via_buffer* viacam_next_buffer (struct via_camera*) ; 
 int viacam_read_reg (struct via_camera*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_dma_copy_out_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t viacam_irq(int irq, void *data)
{
	struct via_camera *cam = data;
	struct via_buffer *vb;
	int bufn;
	struct sg_table *sgt;

	mutex_lock(&cam->lock);
	/*
	 * If there is no place to put the data frame, don't bother
	 * with anything else.
	 */
	vb = viacam_next_buffer(cam);
	if (vb == NULL)
		goto done;
	/*
	 * Figure out which buffer we just completed.
	 */
	bufn = (viacam_read_reg(cam, VCR_INTCTRL) & VCR_IC_ACTBUF) >> 3;
	bufn -= 1;
	if (bufn < 0)
		bufn = cam->n_cap_bufs - 1;
	/*
	 * Copy over the data and let any waiters know.
	 */
	sgt = vb2_dma_sg_plane_desc(&vb->vbuf.vb2_buf, 0);
	vb->vbuf.vb2_buf.timestamp = ktime_get_ns();
	viafb_dma_copy_out_sg(cam->cb_offsets[bufn], sgt->sgl, sgt->nents);
	vb->vbuf.sequence = cam->sequence++;
	vb->vbuf.field = V4L2_FIELD_NONE;
	list_del(&vb->queue);
	vb2_buffer_done(&vb->vbuf.vb2_buf, VB2_BUF_STATE_DONE);
done:
	mutex_unlock(&cam->lock);
	return IRQ_HANDLED;
}