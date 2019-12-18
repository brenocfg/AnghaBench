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
 int CSI_ID_2_SKIP_MASK ; 
 int CSI_ID_2_SKIP_SHIFT ; 
 int CSI_MAX_RATIO_SKIP_SMFC_MASK ; 
 int CSI_MAX_RATIO_SKIP_SMFC_SHIFT ; 
 int /*<<< orphan*/  CSI_SKIP ; 
 int CSI_SKIP_SMFC_MASK ; 
 int CSI_SKIP_SMFC_SHIFT ; 
 int EINVAL ; 
 int ipu_csi_read (struct ipu_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_csi_write (struct ipu_csi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipu_csi_set_skip_smfc(struct ipu_csi *csi, u32 skip,
			  u32 max_ratio, u32 id)
{
	unsigned long flags;
	u32 temp;

	if (max_ratio > 5 || id > 3)
		return -EINVAL;

	spin_lock_irqsave(&csi->lock, flags);

	temp = ipu_csi_read(csi, CSI_SKIP);
	temp &= ~(CSI_MAX_RATIO_SKIP_SMFC_MASK | CSI_ID_2_SKIP_MASK |
		  CSI_SKIP_SMFC_MASK);
	temp |= (max_ratio << CSI_MAX_RATIO_SKIP_SMFC_SHIFT) |
		(id << CSI_ID_2_SKIP_SHIFT) |
		(skip << CSI_SKIP_SMFC_SHIFT);
	ipu_csi_write(csi, temp, CSI_SKIP);

	spin_unlock_irqrestore(&csi->lock, flags);

	return 0;
}