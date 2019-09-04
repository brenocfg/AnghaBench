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
struct ipu_soc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDMAC_BAND_EN (int) ; 
 int /*<<< orphan*/  IDMAC_CHA_EN (int) ; 
 int /*<<< orphan*/  IDMAC_CHA_PRI (int) ; 
 int /*<<< orphan*/  IDMAC_CONF ; 
 int /*<<< orphan*/  IPU_CHA_DB_MODE_SEL (int) ; 
 int /*<<< orphan*/  IPU_CONF ; 
 int /*<<< orphan*/  IPU_FS_DISP_FLOW1 ; 
 int /*<<< orphan*/  IPU_FS_PROC_FLOW1 ; 
 int /*<<< orphan*/  IPU_FS_PROC_FLOW2 ; 
 int /*<<< orphan*/  IPU_FS_PROC_FLOW3 ; 
 int /*<<< orphan*/  IPU_INT_CTRL (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ipu_cm_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 

void ipu_dump(struct ipu_soc *ipu)
{
	int i;

	dev_dbg(ipu->dev, "IPU_CONF = \t0x%08X\n",
		ipu_cm_read(ipu, IPU_CONF));
	dev_dbg(ipu->dev, "IDMAC_CONF = \t0x%08X\n",
		ipu_idmac_read(ipu, IDMAC_CONF));
	dev_dbg(ipu->dev, "IDMAC_CHA_EN1 = \t0x%08X\n",
		ipu_idmac_read(ipu, IDMAC_CHA_EN(0)));
	dev_dbg(ipu->dev, "IDMAC_CHA_EN2 = \t0x%08X\n",
		ipu_idmac_read(ipu, IDMAC_CHA_EN(32)));
	dev_dbg(ipu->dev, "IDMAC_CHA_PRI1 = \t0x%08X\n",
		ipu_idmac_read(ipu, IDMAC_CHA_PRI(0)));
	dev_dbg(ipu->dev, "IDMAC_CHA_PRI2 = \t0x%08X\n",
		ipu_idmac_read(ipu, IDMAC_CHA_PRI(32)));
	dev_dbg(ipu->dev, "IDMAC_BAND_EN1 = \t0x%08X\n",
		ipu_idmac_read(ipu, IDMAC_BAND_EN(0)));
	dev_dbg(ipu->dev, "IDMAC_BAND_EN2 = \t0x%08X\n",
		ipu_idmac_read(ipu, IDMAC_BAND_EN(32)));
	dev_dbg(ipu->dev, "IPU_CHA_DB_MODE_SEL0 = \t0x%08X\n",
		ipu_cm_read(ipu, IPU_CHA_DB_MODE_SEL(0)));
	dev_dbg(ipu->dev, "IPU_CHA_DB_MODE_SEL1 = \t0x%08X\n",
		ipu_cm_read(ipu, IPU_CHA_DB_MODE_SEL(32)));
	dev_dbg(ipu->dev, "IPU_FS_PROC_FLOW1 = \t0x%08X\n",
		ipu_cm_read(ipu, IPU_FS_PROC_FLOW1));
	dev_dbg(ipu->dev, "IPU_FS_PROC_FLOW2 = \t0x%08X\n",
		ipu_cm_read(ipu, IPU_FS_PROC_FLOW2));
	dev_dbg(ipu->dev, "IPU_FS_PROC_FLOW3 = \t0x%08X\n",
		ipu_cm_read(ipu, IPU_FS_PROC_FLOW3));
	dev_dbg(ipu->dev, "IPU_FS_DISP_FLOW1 = \t0x%08X\n",
		ipu_cm_read(ipu, IPU_FS_DISP_FLOW1));
	for (i = 0; i < 15; i++)
		dev_dbg(ipu->dev, "IPU_INT_CTRL(%d) = \t%08X\n", i,
			ipu_cm_read(ipu, IPU_INT_CTRL(i)));
}