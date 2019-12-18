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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct ipu_csi_bus_config {int mipi_dt; } ;
struct ipu_csi {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_MIPI_DI ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_MBUS_CSI2_DPHY ; 
 int ipu_csi_read (struct ipu_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_csi_write (struct ipu_csi*,int,int /*<<< orphan*/ ) ; 
 int mbus_code_to_bus_cfg (struct ipu_csi_bus_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipu_csi_set_mipi_datatype(struct ipu_csi *csi, u32 vc,
			      struct v4l2_mbus_framefmt *mbus_fmt)
{
	struct ipu_csi_bus_config cfg;
	unsigned long flags;
	u32 temp;
	int ret;

	if (vc > 3)
		return -EINVAL;

	ret = mbus_code_to_bus_cfg(&cfg, mbus_fmt->code, V4L2_MBUS_CSI2_DPHY);
	if (ret < 0)
		return ret;

	spin_lock_irqsave(&csi->lock, flags);

	temp = ipu_csi_read(csi, CSI_MIPI_DI);
	temp &= ~(0xff << (vc * 8));
	temp |= (cfg.mipi_dt << (vc * 8));
	ipu_csi_write(csi, temp, CSI_MIPI_DI);

	spin_unlock_irqrestore(&csi->lock, flags);

	return 0;
}