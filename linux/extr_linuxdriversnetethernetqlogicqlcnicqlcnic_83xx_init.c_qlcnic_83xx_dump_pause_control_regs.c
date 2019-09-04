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
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int QLCRD32 (struct qlcnic_adapter*,int,int*) ; 
 int /*<<< orphan*/  QLCWR32 (struct qlcnic_adapter*,int,int) ; 
 int QLC_83XX_PORT0_TC_MC_REG ; 
 int QLC_83XX_PORT0_TC_STATS ; 
 int QLC_83XX_PORT0_THRESHOLD ; 
 int QLC_83XX_PORT1_TC_MC_REG ; 
 int QLC_83XX_PORT1_TC_STATS ; 
 int QLC_83XX_PORT1_THRESHOLD ; 
 int QLC_83XX_PORT2_IFB_THRESHOLD ; 
 int QLC_83XX_PORT3_IFB_THRESHOLD ; 
 int QLC_83XX_SRE_SHIM_REG ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void qlcnic_83xx_dump_pause_control_regs(struct qlcnic_adapter *adapter)
{
	int i, j;
	u32 val = 0, val1 = 0, reg = 0;
	int err = 0;

	val = QLCRD32(adapter, QLC_83XX_SRE_SHIM_REG, &err);
	if (err == -EIO)
		return;
	dev_info(&adapter->pdev->dev, "SRE-Shim Ctrl:0x%x\n", val);

	for (j = 0; j < 2; j++) {
		if (j == 0) {
			dev_info(&adapter->pdev->dev,
				 "Port 0 RxB Pause Threshold Regs[TC7..TC0]:");
			reg = QLC_83XX_PORT0_THRESHOLD;
		} else if (j == 1) {
			dev_info(&adapter->pdev->dev,
				 "Port 1 RxB Pause Threshold Regs[TC7..TC0]:");
			reg = QLC_83XX_PORT1_THRESHOLD;
		}
		for (i = 0; i < 8; i++) {
			val = QLCRD32(adapter, reg + (i * 0x4), &err);
			if (err == -EIO)
				return;
			dev_info(&adapter->pdev->dev, "0x%x  ", val);
		}
		dev_info(&adapter->pdev->dev, "\n");
	}

	for (j = 0; j < 2; j++) {
		if (j == 0) {
			dev_info(&adapter->pdev->dev,
				 "Port 0 RxB TC Max Cell Registers[4..1]:");
			reg = QLC_83XX_PORT0_TC_MC_REG;
		} else if (j == 1) {
			dev_info(&adapter->pdev->dev,
				 "Port 1 RxB TC Max Cell Registers[4..1]:");
			reg = QLC_83XX_PORT1_TC_MC_REG;
		}
		for (i = 0; i < 4; i++) {
			val = QLCRD32(adapter, reg + (i * 0x4), &err);
			if (err == -EIO)
				return;
			dev_info(&adapter->pdev->dev, "0x%x  ", val);
		}
		dev_info(&adapter->pdev->dev, "\n");
	}

	for (j = 0; j < 2; j++) {
		if (j == 0) {
			dev_info(&adapter->pdev->dev,
				 "Port 0 RxB Rx TC Stats[TC7..TC0]:");
			reg = QLC_83XX_PORT0_TC_STATS;
		} else if (j == 1) {
			dev_info(&adapter->pdev->dev,
				 "Port 1 RxB Rx TC Stats[TC7..TC0]:");
			reg = QLC_83XX_PORT1_TC_STATS;
		}
		for (i = 7; i >= 0; i--) {
			val = QLCRD32(adapter, reg, &err);
			if (err == -EIO)
				return;
			val &= ~(0x7 << 29);    /* Reset bits 29 to 31 */
			QLCWR32(adapter, reg, (val | (i << 29)));
			val = QLCRD32(adapter, reg, &err);
			if (err == -EIO)
				return;
			dev_info(&adapter->pdev->dev, "0x%x  ", val);
		}
		dev_info(&adapter->pdev->dev, "\n");
	}

	val = QLCRD32(adapter, QLC_83XX_PORT2_IFB_THRESHOLD, &err);
	if (err == -EIO)
		return;
	val1 = QLCRD32(adapter, QLC_83XX_PORT3_IFB_THRESHOLD, &err);
	if (err == -EIO)
		return;
	dev_info(&adapter->pdev->dev,
		 "IFB-Pause Thresholds: Port 2:0x%x, Port 3:0x%x\n",
		 val, val1);
}