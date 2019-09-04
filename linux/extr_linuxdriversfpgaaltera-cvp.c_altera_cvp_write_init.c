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
struct fpga_image_info {int flags; } ;
struct altera_cvp_conf {int numclks; struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int FPGA_MGR_COMPRESSED_BITSTREAM ; 
 int FPGA_MGR_ENCRYPTED_BITSTREAM ; 
 int FPGA_MGR_PARTIAL_RECONFIG ; 
 int /*<<< orphan*/  VSE_CVP_MODE_CTRL ; 
 int VSE_CVP_MODE_CTRL_CVP_MODE ; 
 int VSE_CVP_MODE_CTRL_HIP_CLK_SEL ; 
 int VSE_CVP_MODE_CTRL_NUMCLKS_MASK ; 
 int VSE_CVP_MODE_CTRL_NUMCLKS_OFF ; 
 int /*<<< orphan*/  VSE_CVP_PROG_CTRL ; 
 int VSE_CVP_PROG_CTRL_CONFIG ; 
 int VSE_CVP_PROG_CTRL_START_XFER ; 
 int /*<<< orphan*/  VSE_CVP_STATUS ; 
 int VSE_CVP_STATUS_CFG_RDY ; 
 int VSE_CVP_STATUS_CVP_EN ; 
 int /*<<< orphan*/  altera_cvp_dummy_write (struct altera_cvp_conf*) ; 
 int altera_cvp_teardown (struct fpga_manager*,struct fpga_image_info*) ; 
 int altera_cvp_wait_status (struct altera_cvp_conf*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int altera_cvp_write_init(struct fpga_manager *mgr,
				 struct fpga_image_info *info,
				 const char *buf, size_t count)
{
	struct altera_cvp_conf *conf = mgr->priv;
	struct pci_dev *pdev = conf->pci_dev;
	u32 iflags, val;
	int ret;

	iflags = info ? info->flags : 0;

	if (iflags & FPGA_MGR_PARTIAL_RECONFIG) {
		dev_err(&mgr->dev, "Partial reconfiguration not supported.\n");
		return -EINVAL;
	}

	/* Determine allowed clock to data ratio */
	if (iflags & FPGA_MGR_COMPRESSED_BITSTREAM)
		conf->numclks = 8; /* ratio for all compressed images */
	else if (iflags & FPGA_MGR_ENCRYPTED_BITSTREAM)
		conf->numclks = 4; /* for uncompressed and encrypted images */
	else
		conf->numclks = 1; /* for uncompressed and unencrypted images */

	/* STEP 1 - read CVP status and check CVP_EN flag */
	pci_read_config_dword(pdev, VSE_CVP_STATUS, &val);
	if (!(val & VSE_CVP_STATUS_CVP_EN)) {
		dev_err(&mgr->dev, "CVP mode off: 0x%04x\n", val);
		return -ENODEV;
	}

	if (val & VSE_CVP_STATUS_CFG_RDY) {
		dev_warn(&mgr->dev, "CvP already started, teardown first\n");
		ret = altera_cvp_teardown(mgr, info);
		if (ret)
			return ret;
	}

	/*
	 * STEP 2
	 * - set HIP_CLK_SEL and CVP_MODE (must be set in the order mentioned)
	 */
	/* switch from fabric to PMA clock */
	pci_read_config_dword(pdev, VSE_CVP_MODE_CTRL, &val);
	val |= VSE_CVP_MODE_CTRL_HIP_CLK_SEL;
	pci_write_config_dword(pdev, VSE_CVP_MODE_CTRL, val);

	/* set CVP mode */
	pci_read_config_dword(pdev, VSE_CVP_MODE_CTRL, &val);
	val |= VSE_CVP_MODE_CTRL_CVP_MODE;
	pci_write_config_dword(pdev, VSE_CVP_MODE_CTRL, val);

	/*
	 * STEP 3
	 * - set CVP_NUMCLKS to 1 and issue CVP_DUMMY_WR dummy writes to the HIP
	 */
	altera_cvp_dummy_write(conf);

	/* STEP 4 - set CVP_CONFIG bit */
	pci_read_config_dword(pdev, VSE_CVP_PROG_CTRL, &val);
	/* request control block to begin transfer using CVP */
	val |= VSE_CVP_PROG_CTRL_CONFIG;
	pci_write_config_dword(pdev, VSE_CVP_PROG_CTRL, val);

	/* STEP 5 - poll CVP_CONFIG READY for 1 with 10us timeout */
	ret = altera_cvp_wait_status(conf, VSE_CVP_STATUS_CFG_RDY,
				     VSE_CVP_STATUS_CFG_RDY, 10);
	if (ret) {
		dev_warn(&mgr->dev, "CFG_RDY == 1 timeout\n");
		return ret;
	}

	/*
	 * STEP 6
	 * - set CVP_NUMCLKS to 1 and issue CVP_DUMMY_WR dummy writes to the HIP
	 */
	altera_cvp_dummy_write(conf);

	/* STEP 7 - set START_XFER */
	pci_read_config_dword(pdev, VSE_CVP_PROG_CTRL, &val);
	val |= VSE_CVP_PROG_CTRL_START_XFER;
	pci_write_config_dword(pdev, VSE_CVP_PROG_CTRL, val);

	/* STEP 8 - start transfer (set CVP_NUMCLKS for bitstream) */
	pci_read_config_dword(pdev, VSE_CVP_MODE_CTRL, &val);
	val &= ~VSE_CVP_MODE_CTRL_NUMCLKS_MASK;
	val |= conf->numclks << VSE_CVP_MODE_CTRL_NUMCLKS_OFF;
	pci_write_config_dword(pdev, VSE_CVP_MODE_CTRL, val);

	return 0;
}