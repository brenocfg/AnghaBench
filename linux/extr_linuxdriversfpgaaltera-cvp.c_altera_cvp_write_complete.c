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
struct pci_dev {int dummy; } ;
struct fpga_manager {int /*<<< orphan*/  dev; struct altera_cvp_conf* priv; } ;
struct fpga_image_info {int dummy; } ;
struct altera_cvp_conf {struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  TIMEOUT_US ; 
 int /*<<< orphan*/  VSE_CVP_MODE_CTRL ; 
 int VSE_CVP_MODE_CTRL_CVP_MODE ; 
 int VSE_CVP_MODE_CTRL_HIP_CLK_SEL ; 
 int VSE_CVP_STATUS_PLD_CLK_IN_USE ; 
 int VSE_CVP_STATUS_USERMODE ; 
 int VSE_UNCOR_ERR_CVP_CFG_ERR ; 
 int /*<<< orphan*/  VSE_UNCOR_ERR_STATUS ; 
 int altera_cvp_teardown (struct fpga_manager*,struct fpga_image_info*) ; 
 int altera_cvp_wait_status (struct altera_cvp_conf*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int altera_cvp_write_complete(struct fpga_manager *mgr,
				     struct fpga_image_info *info)
{
	struct altera_cvp_conf *conf = mgr->priv;
	struct pci_dev *pdev = conf->pci_dev;
	int ret;
	u32 mask;
	u32 val;

	ret = altera_cvp_teardown(mgr, info);
	if (ret)
		return ret;

	/* STEP 16 - check CVP_CONFIG_ERROR_LATCHED bit */
	pci_read_config_dword(pdev, VSE_UNCOR_ERR_STATUS, &val);
	if (val & VSE_UNCOR_ERR_CVP_CFG_ERR) {
		dev_err(&mgr->dev, "detected CVP_CONFIG_ERROR_LATCHED!\n");
		return -EPROTO;
	}

	/* STEP 17 - reset CVP_MODE and HIP_CLK_SEL bit */
	pci_read_config_dword(pdev, VSE_CVP_MODE_CTRL, &val);
	val &= ~VSE_CVP_MODE_CTRL_HIP_CLK_SEL;
	val &= ~VSE_CVP_MODE_CTRL_CVP_MODE;
	pci_write_config_dword(pdev, VSE_CVP_MODE_CTRL, val);

	/* STEP 18 - poll PLD_CLK_IN_USE and USER_MODE bits */
	mask = VSE_CVP_STATUS_PLD_CLK_IN_USE | VSE_CVP_STATUS_USERMODE;
	ret = altera_cvp_wait_status(conf, mask, mask, TIMEOUT_US);
	if (ret)
		dev_err(&mgr->dev, "PLD_CLK_IN_USE|USERMODE timeout\n");

	return ret;
}