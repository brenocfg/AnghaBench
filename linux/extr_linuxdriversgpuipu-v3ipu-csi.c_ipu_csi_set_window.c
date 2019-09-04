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
typedef  int u32 ;
struct v4l2_rect {int width; int height; int top; int left; } ;
struct ipu_csi {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_ACT_FRM_SIZE ; 
 int CSI_HSC_MASK ; 
 int CSI_HSC_SHIFT ; 
 int /*<<< orphan*/  CSI_OUT_FRM_CTRL ; 
 int CSI_VSC_MASK ; 
 int CSI_VSC_SHIFT ; 
 int ipu_csi_read (struct ipu_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_csi_write (struct ipu_csi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipu_csi_set_window(struct ipu_csi *csi, struct v4l2_rect *w)
{
	unsigned long flags;
	u32 reg;

	spin_lock_irqsave(&csi->lock, flags);

	ipu_csi_write(csi, (w->width - 1) | ((w->height - 1) << 16),
			  CSI_ACT_FRM_SIZE);

	reg = ipu_csi_read(csi, CSI_OUT_FRM_CTRL);
	reg &= ~(CSI_HSC_MASK | CSI_VSC_MASK);
	reg |= ((w->top << CSI_VSC_SHIFT) | (w->left << CSI_HSC_SHIFT));
	ipu_csi_write(csi, reg, CSI_OUT_FRM_CTRL);

	spin_unlock_irqrestore(&csi->lock, flags);
}