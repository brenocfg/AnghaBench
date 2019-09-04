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
struct emmaprp_dev {int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  irqlock; scalar_t__ base_emma; } ;
struct emmaprp_ctx {int /*<<< orphan*/  m2m_ctx; int /*<<< orphan*/  aborting; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PRP_CNTL ; 
 int PRP_CNTL_SWRST ; 
 scalar_t__ PRP_INTRSTATUS ; 
 int PRP_INTR_ST_CH2B1CI ; 
 int PRP_INTR_ST_CH2WERR ; 
 int PRP_INTR_ST_RDERR ; 
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  dprintk (struct emmaprp_dev*,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct emmaprp_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t emmaprp_irq(int irq_emma, void *data)
{
	struct emmaprp_dev *pcdev = data;
	struct emmaprp_ctx *curr_ctx;
	struct vb2_v4l2_buffer *src_vb, *dst_vb;
	unsigned long flags;
	u32 irqst;

	/* Check irq flags and clear irq */
	irqst = readl(pcdev->base_emma + PRP_INTRSTATUS);
	writel(irqst, pcdev->base_emma + PRP_INTRSTATUS);
	dprintk(pcdev, "irqst = 0x%08x\n", irqst);

	curr_ctx = v4l2_m2m_get_curr_priv(pcdev->m2m_dev);
	if (curr_ctx == NULL) {
		pr_err("Instance released before the end of transaction\n");
		return IRQ_HANDLED;
	}

	if (!curr_ctx->aborting) {
		if ((irqst & PRP_INTR_ST_RDERR) ||
		(irqst & PRP_INTR_ST_CH2WERR)) {
			pr_err("PrP bus error occurred, this transfer is probably corrupted\n");
			writel(PRP_CNTL_SWRST, pcdev->base_emma + PRP_CNTL);
		} else if (irqst & PRP_INTR_ST_CH2B1CI) { /* buffer ready */
			src_vb = v4l2_m2m_src_buf_remove(curr_ctx->m2m_ctx);
			dst_vb = v4l2_m2m_dst_buf_remove(curr_ctx->m2m_ctx);

			dst_vb->vb2_buf.timestamp = src_vb->vb2_buf.timestamp;
			dst_vb->flags &=
				~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
			dst_vb->flags |=
				src_vb->flags
				& V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
			dst_vb->timecode = src_vb->timecode;

			spin_lock_irqsave(&pcdev->irqlock, flags);
			v4l2_m2m_buf_done(src_vb, VB2_BUF_STATE_DONE);
			v4l2_m2m_buf_done(dst_vb, VB2_BUF_STATE_DONE);
			spin_unlock_irqrestore(&pcdev->irqlock, flags);
		}
	}

	v4l2_m2m_job_finish(pcdev->m2m_dev, curr_ctx->m2m_ctx);
	return IRQ_HANDLED;
}