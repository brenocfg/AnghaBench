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
typedef  int /*<<< orphan*/  u32 ;
struct ipu_soc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_CONF ; 
 int /*<<< orphan*/  IPU_CONF_CSI0_DATA_SOURCE ; 
 int /*<<< orphan*/  IPU_CONF_CSI1_DATA_SOURCE ; 
 int /*<<< orphan*/  ipu_cm_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_cm_write (struct ipu_soc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipu_set_csi_src_mux(struct ipu_soc *ipu, int csi_id, bool mipi_csi2)
{
	unsigned long flags;
	u32 val, mask;

	mask = (csi_id == 1) ? IPU_CONF_CSI1_DATA_SOURCE :
		IPU_CONF_CSI0_DATA_SOURCE;

	spin_lock_irqsave(&ipu->lock, flags);

	val = ipu_cm_read(ipu, IPU_CONF);
	if (mipi_csi2)
		val |= mask;
	else
		val &= ~mask;
	ipu_cm_write(ipu, val, IPU_CONF);

	spin_unlock_irqrestore(&ipu->lock, flags);
}