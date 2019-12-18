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
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AM_CURR_TRANS_RETURN ; 
 int /*<<< orphan*/  AXI_CFG ; 
 scalar_t__ AXI_MASTER_CFG_BASE ; 
 int BIT (int) ; 
 int /*<<< orphan*/  DMA_TX_DFX1 ; 
 int /*<<< orphan*/  DMA_TX_FIFO_DFX0 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int,int,int,int) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int hisi_sas_read32_relaxed (struct hisi_hba*,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool axi_bus_is_idle_v2_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	int i, max_loop = 1000;
	struct device *dev = hisi_hba->dev;
	u32 status, axi_status, dfx_val, dfx_tx_val;

	for (i = 0; i < max_loop; i++) {
		status = hisi_sas_read32_relaxed(hisi_hba,
			AXI_MASTER_CFG_BASE + AM_CURR_TRANS_RETURN);

		axi_status = hisi_sas_read32(hisi_hba, AXI_CFG);
		dfx_val = hisi_sas_phy_read32(hisi_hba, phy_no, DMA_TX_DFX1);
		dfx_tx_val = hisi_sas_phy_read32(hisi_hba,
			phy_no, DMA_TX_FIFO_DFX0);

		if ((status == 0x3) && (axi_status == 0x0) &&
		    (dfx_val & BIT(20)) && (dfx_tx_val & BIT(10)))
			return true;
		udelay(10);
	}
	dev_err(dev, "bus is not idle phy%d, axi150:0x%x axi100:0x%x port204:0x%x port240:0x%x\n",
			phy_no, status, axi_status,
			dfx_val, dfx_tx_val);
	return false;
}