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
struct pci_dev {int revision; } ;
struct hisi_sas_hw_error {int irq_msk; int msk; scalar_t__ msg; scalar_t__ reg; struct hisi_sas_hw_error* sub; } ;
struct hisi_sas_device {int /*<<< orphan*/  completion; } ;
struct hisi_hba {struct hisi_sas_device* devices; int /*<<< orphan*/  rst_work; int /*<<< orphan*/  wq; struct pci_dev* pci_dev; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ AM_CTRL_GLOBAL ; 
 int AM_CTRL_SHUTDOWN_REQ_MSK ; 
 int ARRAY_SIZE (struct hisi_sas_hw_error*) ; 
 scalar_t__ AXI_MASTER_CFG_BASE ; 
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ ENT_INT_SRC3 ; 
 int /*<<< orphan*/  ENT_INT_SRC3_ITC_INT_OFF ; 
 scalar_t__ ENT_INT_SRC_MSK3 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ ITCT_CLR ; 
 int ITCT_DEV_MSK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,int) ; 
 struct hisi_sas_hw_error* fatal_axi_error ; 
 int /*<<< orphan*/  fatal_ecc_int_v3_hw (struct hisi_hba*) ; 
 int hisi_sas_read32 (struct hisi_hba*,scalar_t__) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,scalar_t__,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t fatal_axi_int_v3_hw(int irq_no, void *p)
{
	u32 irq_value, irq_msk;
	struct hisi_hba *hisi_hba = p;
	struct device *dev = hisi_hba->dev;
	struct pci_dev *pdev = hisi_hba->pci_dev;
	int i;

	irq_msk = hisi_sas_read32(hisi_hba, ENT_INT_SRC_MSK3);
	hisi_sas_write32(hisi_hba, ENT_INT_SRC_MSK3, irq_msk | 0x1df00);

	irq_value = hisi_sas_read32(hisi_hba, ENT_INT_SRC3);
	irq_value &= ~irq_msk;

	for (i = 0; i < ARRAY_SIZE(fatal_axi_error); i++) {
		const struct hisi_sas_hw_error *error = &fatal_axi_error[i];

		if (!(irq_value & error->irq_msk))
			continue;

		if (error->sub) {
			const struct hisi_sas_hw_error *sub = error->sub;
			u32 err_value = hisi_sas_read32(hisi_hba, error->reg);

			for (; sub->msk || sub->msg; sub++) {
				if (!(err_value & sub->msk))
					continue;

				dev_err(dev, "%s error (0x%x) found!\n",
					sub->msg, irq_value);
				queue_work(hisi_hba->wq, &hisi_hba->rst_work);
			}
		} else {
			dev_err(dev, "%s error (0x%x) found!\n",
				error->msg, irq_value);
			queue_work(hisi_hba->wq, &hisi_hba->rst_work);
		}

		if (pdev->revision < 0x21) {
			u32 reg_val;

			reg_val = hisi_sas_read32(hisi_hba,
						  AXI_MASTER_CFG_BASE +
						  AM_CTRL_GLOBAL);
			reg_val |= AM_CTRL_SHUTDOWN_REQ_MSK;
			hisi_sas_write32(hisi_hba, AXI_MASTER_CFG_BASE +
					 AM_CTRL_GLOBAL, reg_val);
		}
	}

	fatal_ecc_int_v3_hw(hisi_hba);

	if (irq_value & BIT(ENT_INT_SRC3_ITC_INT_OFF)) {
		u32 reg_val = hisi_sas_read32(hisi_hba, ITCT_CLR);
		u32 dev_id = reg_val & ITCT_DEV_MSK;
		struct hisi_sas_device *sas_dev =
				&hisi_hba->devices[dev_id];

		hisi_sas_write32(hisi_hba, ITCT_CLR, 0);
		dev_dbg(dev, "clear ITCT ok\n");
		complete(sas_dev->completion);
	}

	hisi_sas_write32(hisi_hba, ENT_INT_SRC3, irq_value & 0x1df00);
	hisi_sas_write32(hisi_hba, ENT_INT_SRC_MSK3, irq_msk);

	return IRQ_HANDLED;
}