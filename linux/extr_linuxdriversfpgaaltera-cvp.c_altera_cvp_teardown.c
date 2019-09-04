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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct fpga_manager {int /*<<< orphan*/  dev; struct altera_cvp_conf* priv; } ;
struct fpga_image_info {int dummy; } ;
struct altera_cvp_conf {struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VSE_CVP_PROG_CTRL ; 
 int /*<<< orphan*/  VSE_CVP_PROG_CTRL_CONFIG ; 
 int /*<<< orphan*/  VSE_CVP_PROG_CTRL_START_XFER ; 
 int /*<<< orphan*/  VSE_CVP_STATUS_CFG_RDY ; 
 int /*<<< orphan*/  altera_cvp_dummy_write (struct altera_cvp_conf*) ; 
 int altera_cvp_wait_status (struct altera_cvp_conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int altera_cvp_teardown(struct fpga_manager *mgr,
			       struct fpga_image_info *info)
{
	struct altera_cvp_conf *conf = mgr->priv;
	struct pci_dev *pdev = conf->pci_dev;
	int ret;
	u32 val;

	/* STEP 12 - reset START_XFER bit */
	pci_read_config_dword(pdev, VSE_CVP_PROG_CTRL, &val);
	val &= ~VSE_CVP_PROG_CTRL_START_XFER;
	pci_write_config_dword(pdev, VSE_CVP_PROG_CTRL, val);

	/* STEP 13 - reset CVP_CONFIG bit */
	val &= ~VSE_CVP_PROG_CTRL_CONFIG;
	pci_write_config_dword(pdev, VSE_CVP_PROG_CTRL, val);

	/*
	 * STEP 14
	 * - set CVP_NUMCLKS to 1 and then issue CVP_DUMMY_WR dummy
	 *   writes to the HIP
	 */
	altera_cvp_dummy_write(conf); /* from CVP clock to internal clock */

	/* STEP 15 - poll CVP_CONFIG_READY bit for 0 with 10us timeout */
	ret = altera_cvp_wait_status(conf, VSE_CVP_STATUS_CFG_RDY, 0, 10);
	if (ret)
		dev_err(&mgr->dev, "CFG_RDY == 0 timeout\n");

	return ret;
}