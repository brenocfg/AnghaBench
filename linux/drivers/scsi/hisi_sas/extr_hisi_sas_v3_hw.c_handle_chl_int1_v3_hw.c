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
struct hisi_sas_hw_error {int irq_msk; int /*<<< orphan*/  msg; } ;
struct hisi_hba {int /*<<< orphan*/  rst_work; int /*<<< orphan*/  wq; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct hisi_sas_hw_error*) ; 
 int /*<<< orphan*/  CHL_INT1 ; 
 int /*<<< orphan*/  CHL_INT1_MSK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int,int) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 
 struct hisi_sas_hw_error* port_axi_error ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_chl_int1_v3_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	u32 irq_value = hisi_sas_phy_read32(hisi_hba, phy_no, CHL_INT1);
	u32 irq_msk = hisi_sas_phy_read32(hisi_hba, phy_no, CHL_INT1_MSK);
	struct device *dev = hisi_hba->dev;
	int i;

	irq_value &= ~irq_msk;
	if (!irq_value)
		return;

	for (i = 0; i < ARRAY_SIZE(port_axi_error); i++) {
		const struct hisi_sas_hw_error *error = &port_axi_error[i];

		if (!(irq_value & error->irq_msk))
			continue;

		dev_err(dev, "%s error (phy%d 0x%x) found!\n",
			error->msg, phy_no, irq_value);
		queue_work(hisi_hba->wq, &hisi_hba->rst_work);
	}

	hisi_sas_phy_write32(hisi_hba, phy_no, CHL_INT1, irq_value);
}