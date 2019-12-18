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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENT_INT_SRC2 ; 
 int ENT_INT_SRC2_AXI_OVERLF_INT_MSK ; 
 int ENT_INT_SRC2_AXI_WRONG_INT_MSK ; 
 int ENT_INT_SRC2_CQ_CFG_ERR_MSK ; 
 int ENT_INT_SRC2_DQ_CFG_ERR_MSK ; 
 int /*<<< orphan*/  HGC_AXI_FIFO_ERR_INFO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t fatal_axi_int_v1_hw(int irq, void *p)
{
	struct hisi_hba *hisi_hba = p;
	struct device *dev = hisi_hba->dev;
	u32 axi_int = hisi_sas_read32(hisi_hba, ENT_INT_SRC2);
	u32 axi_info = hisi_sas_read32(hisi_hba, HGC_AXI_FIFO_ERR_INFO);

	if (axi_int & ENT_INT_SRC2_DQ_CFG_ERR_MSK)
		panic("%s: Fatal DQ_CFG_ERR interrupt (0x%x)\n",
		      dev_name(dev), axi_info);

	if (axi_int & ENT_INT_SRC2_CQ_CFG_ERR_MSK)
		panic("%s: Fatal CQ_CFG_ERR interrupt (0x%x)\n",
		      dev_name(dev), axi_info);

	if (axi_int & ENT_INT_SRC2_AXI_WRONG_INT_MSK)
		panic("%s: Fatal AXI_WRONG_INT interrupt (0x%x)\n",
		      dev_name(dev), axi_info);

	if (axi_int & ENT_INT_SRC2_AXI_OVERLF_INT_MSK)
		panic("%s: Fatal AXI_OVERLF_INT incorrect interrupt (0x%x)\n",
		      dev_name(dev), axi_info);

	hisi_sas_write32(hisi_hba, ENT_INT_SRC2, axi_int | 0x30000000);

	return IRQ_HANDLED;
}