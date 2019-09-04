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
struct ipu_csi {int /*<<< orphan*/  id; TYPE_1__* ipu; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_SENS_CONF ; 
 int CSI_SENS_CONF_SENS_PRTCL_MASK ; 
 int CSI_SENS_CONF_SENS_PRTCL_SHIFT ; 
#define  IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_DDR 135 
#define  IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_SDR 134 
#define  IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_DDR 133 
#define  IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_SDR 132 
#define  IPU_CSI_CLK_MODE_CCIR656_INTERLACED 131 
#define  IPU_CSI_CLK_MODE_CCIR656_PROGRESSIVE 130 
#define  IPU_CSI_CLK_MODE_GATED_CLK 129 
#define  IPU_CSI_CLK_MODE_NONGATED_CLK 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ipu_csi_read (struct ipu_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool ipu_csi_is_interlaced(struct ipu_csi *csi)
{
	unsigned long flags;
	u32 sensor_protocol;

	spin_lock_irqsave(&csi->lock, flags);
	sensor_protocol =
		(ipu_csi_read(csi, CSI_SENS_CONF) &
		 CSI_SENS_CONF_SENS_PRTCL_MASK) >>
		CSI_SENS_CONF_SENS_PRTCL_SHIFT;
	spin_unlock_irqrestore(&csi->lock, flags);

	switch (sensor_protocol) {
	case IPU_CSI_CLK_MODE_GATED_CLK:
	case IPU_CSI_CLK_MODE_NONGATED_CLK:
	case IPU_CSI_CLK_MODE_CCIR656_PROGRESSIVE:
	case IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_DDR:
	case IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_SDR:
		return false;
	case IPU_CSI_CLK_MODE_CCIR656_INTERLACED:
	case IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_DDR:
	case IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_SDR:
		return true;
	default:
		dev_err(csi->ipu->dev,
			"CSI %d sensor protocol unsupported\n", csi->id);
		return false;
	}
}