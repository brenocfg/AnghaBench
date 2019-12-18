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
struct ipu_csi {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CSI_HORI_DOWNSIZE_EN ; 
 int /*<<< orphan*/  CSI_OUT_FRM_CTRL ; 
 int CSI_VERT_DOWNSIZE_EN ; 
 int ipu_csi_read (struct ipu_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_csi_write (struct ipu_csi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipu_csi_set_downsize(struct ipu_csi *csi, bool horiz, bool vert)
{
	unsigned long flags;
	u32 reg;

	spin_lock_irqsave(&csi->lock, flags);

	reg = ipu_csi_read(csi, CSI_OUT_FRM_CTRL);
	reg &= ~(CSI_HORI_DOWNSIZE_EN | CSI_VERT_DOWNSIZE_EN);
	reg |= (horiz ? CSI_HORI_DOWNSIZE_EN : 0) |
	       (vert ? CSI_VERT_DOWNSIZE_EN : 0);
	ipu_csi_write(csi, reg, CSI_OUT_FRM_CTRL);

	spin_unlock_irqrestore(&csi->lock, flags);
}