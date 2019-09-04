#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct videobuf_dmabuf {int /*<<< orphan*/  sglen; int /*<<< orphan*/  sglist; } ;
struct videobuf_buffer {int /*<<< orphan*/  done; int /*<<< orphan*/  size; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  sizeimage; } ;
struct via_camera {int n_cap_bufs; TYPE_1__ user_format; int /*<<< orphan*/ * cb_offsets; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int VCR_IC_ACTBUF ; 
 int /*<<< orphan*/  VCR_INTCTRL ; 
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 struct videobuf_buffer* viacam_next_buffer (struct via_camera*) ; 
 int viacam_read_reg (struct via_camera*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_dma_copy_out_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct videobuf_dmabuf* videobuf_to_dma (struct videobuf_buffer*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t viacam_irq(int irq, void *data)
{
	int bufn;
	struct videobuf_buffer *vb;
	struct via_camera *cam = data;
	struct videobuf_dmabuf *vdma;

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
	vdma = videobuf_to_dma(vb);
	viafb_dma_copy_out_sg(cam->cb_offsets[bufn], vdma->sglist, vdma->sglen);
	vb->state = VIDEOBUF_DONE;
	vb->size = cam->user_format.sizeimage;
	wake_up(&vb->done);
done:
	return IRQ_HANDLED;
}