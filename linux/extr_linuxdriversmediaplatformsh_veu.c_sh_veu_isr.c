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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {int flags; int /*<<< orphan*/  timecode; TYPE_1__ vb2_buf; } ;
struct sh_veu_dev {int /*<<< orphan*/  xaction; int /*<<< orphan*/  lock; int /*<<< orphan*/  m2m_ctx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  VEU_EIER ; 
 int /*<<< orphan*/  VEU_EVTR ; 
 int /*<<< orphan*/  VEU_STR ; 
 int sh_veu_reg_read (struct sh_veu_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_veu_reg_write (struct sh_veu_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sh_veu_isr(int irq, void *dev_id)
{
	struct sh_veu_dev *veu = dev_id;
	struct vb2_v4l2_buffer *dst;
	struct vb2_v4l2_buffer *src;
	u32 status = sh_veu_reg_read(veu, VEU_EVTR);

	/* bundle read mode not used */
	if (!(status & 1))
		return IRQ_NONE;

	/* disable interrupt in VEU */
	sh_veu_reg_write(veu, VEU_EIER, 0);
	/* halt operation */
	sh_veu_reg_write(veu, VEU_STR, 0);
	/* ack int, write 0 to clear bits */
	sh_veu_reg_write(veu, VEU_EVTR, status & ~1);

	/* conversion completed */
	dst = v4l2_m2m_dst_buf_remove(veu->m2m_ctx);
	src = v4l2_m2m_src_buf_remove(veu->m2m_ctx);
	if (!src || !dst)
		return IRQ_NONE;

	dst->vb2_buf.timestamp = src->vb2_buf.timestamp;
	dst->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	dst->flags |=
		src->flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	dst->timecode = src->timecode;

	spin_lock(&veu->lock);
	v4l2_m2m_buf_done(src, VB2_BUF_STATE_DONE);
	v4l2_m2m_buf_done(dst, VB2_BUF_STATE_DONE);
	spin_unlock(&veu->lock);

	veu->xaction++;

	return IRQ_WAKE_THREAD;
}