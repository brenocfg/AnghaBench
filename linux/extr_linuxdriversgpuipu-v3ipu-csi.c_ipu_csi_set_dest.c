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
typedef  enum ipu_csi_dest { ____Placeholder_ipu_csi_dest } ipu_csi_dest ;

/* Variables and functions */
 int CSI_DATA_DEST_IC ; 
 int CSI_DATA_DEST_IDMAC ; 
 int /*<<< orphan*/  CSI_SENS_CONF ; 
 int CSI_SENS_CONF_DATA_DEST_MASK ; 
 int CSI_SENS_CONF_DATA_DEST_SHIFT ; 
 int IPU_CSI_DEST_IDMAC ; 
 int ipu_csi_read (struct ipu_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_csi_write (struct ipu_csi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipu_csi_set_dest(struct ipu_csi *csi, enum ipu_csi_dest csi_dest)
{
	unsigned long flags;
	u32 csi_sens_conf, dest;

	if (csi_dest == IPU_CSI_DEST_IDMAC)
		dest = CSI_DATA_DEST_IDMAC;
	else
		dest = CSI_DATA_DEST_IC; /* IC or VDIC */

	spin_lock_irqsave(&csi->lock, flags);

	csi_sens_conf = ipu_csi_read(csi, CSI_SENS_CONF);
	csi_sens_conf &= ~CSI_SENS_CONF_DATA_DEST_MASK;
	csi_sens_conf |= (dest << CSI_SENS_CONF_DATA_DEST_SHIFT);
	ipu_csi_write(csi, csi_sens_conf, CSI_SENS_CONF);

	spin_unlock_irqrestore(&csi->lock, flags);

	return 0;
}