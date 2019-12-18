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
typedef  scalar_t__ u32 ;
struct hisi_hba {int n_phy; int /*<<< orphan*/  ctrl_reset_sts_reg; scalar_t__ ctrl; scalar_t__ ctrl_clock_ena_reg; scalar_t__ ctrl_reset_reg; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  AXI_CFG ; 
 int /*<<< orphan*/  DMA_RX_STATUS ; 
 scalar_t__ DMA_RX_STATUS_BUSY_MSK ; 
 int /*<<< orphan*/  DMA_TX_STATUS ; 
 scalar_t__ DMA_TX_STATUS_BUSY_MSK ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  PHY_CTRL ; 
 scalar_t__ PHY_CTRL_RESET_MSK ; 
 scalar_t__ RESET_VALUE ; 
 int /*<<< orphan*/  acpi_evaluate_object (scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 scalar_t__ hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_read (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  regmap_write (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int reset_hw_v1_hw(struct hisi_hba *hisi_hba)
{
	int i;
	unsigned long end_time;
	u32 val;
	struct device *dev = hisi_hba->dev;

	for (i = 0; i < hisi_hba->n_phy; i++) {
		u32 phy_ctrl = hisi_sas_phy_read32(hisi_hba, i, PHY_CTRL);

		phy_ctrl |= PHY_CTRL_RESET_MSK;
		hisi_sas_phy_write32(hisi_hba, i, PHY_CTRL, phy_ctrl);
	}
	msleep(1); /* It is safe to wait for 50us */

	/* Ensure DMA tx & rx idle */
	for (i = 0; i < hisi_hba->n_phy; i++) {
		u32 dma_tx_status, dma_rx_status;

		end_time = jiffies + msecs_to_jiffies(1000);

		while (1) {
			dma_tx_status = hisi_sas_phy_read32(hisi_hba, i,
							    DMA_TX_STATUS);
			dma_rx_status = hisi_sas_phy_read32(hisi_hba, i,
							    DMA_RX_STATUS);

			if (!(dma_tx_status & DMA_TX_STATUS_BUSY_MSK) &&
				!(dma_rx_status & DMA_RX_STATUS_BUSY_MSK))
				break;

			msleep(20);
			if (time_after(jiffies, end_time))
				return -EIO;
		}
	}

	/* Ensure axi bus idle */
	end_time = jiffies + msecs_to_jiffies(1000);
	while (1) {
		u32 axi_status =
			hisi_sas_read32(hisi_hba, AXI_CFG);

		if (axi_status == 0)
			break;

		msleep(20);
		if (time_after(jiffies, end_time))
			return -EIO;
	}

	if (ACPI_HANDLE(dev)) {
		acpi_status s;

		s = acpi_evaluate_object(ACPI_HANDLE(dev), "_RST", NULL, NULL);
		if (ACPI_FAILURE(s)) {
			dev_err(dev, "Reset failed\n");
			return -EIO;
		}
	} else if (hisi_hba->ctrl) {
		/* Apply reset and disable clock */
		/* clk disable reg is offset by +4 bytes from clk enable reg */
		regmap_write(hisi_hba->ctrl, hisi_hba->ctrl_reset_reg,
			     RESET_VALUE);
		regmap_write(hisi_hba->ctrl, hisi_hba->ctrl_clock_ena_reg + 4,
			     RESET_VALUE);
		msleep(1);
		regmap_read(hisi_hba->ctrl, hisi_hba->ctrl_reset_sts_reg, &val);
		if (RESET_VALUE != (val & RESET_VALUE)) {
			dev_err(dev, "Reset failed\n");
			return -EIO;
		}

		/* De-reset and enable clock */
		/* deassert rst reg is offset by +4 bytes from assert reg */
		regmap_write(hisi_hba->ctrl, hisi_hba->ctrl_reset_reg + 4,
			     RESET_VALUE);
		regmap_write(hisi_hba->ctrl, hisi_hba->ctrl_clock_ena_reg,
			     RESET_VALUE);
		msleep(1);
		regmap_read(hisi_hba->ctrl, hisi_hba->ctrl_reset_sts_reg, &val);
		if (val & RESET_VALUE) {
			dev_err(dev, "De-reset failed\n");
			return -EIO;
		}
	} else {
		dev_warn(dev, "no reset method\n");
		return -EINVAL;
	}

	return 0;
}