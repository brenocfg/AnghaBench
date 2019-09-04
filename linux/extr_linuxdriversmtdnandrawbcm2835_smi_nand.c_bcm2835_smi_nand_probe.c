#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smi_settings {int read_setup_time; int read_hold_time; int read_pace_time; int read_strobe_time; int write_setup_time; int write_hold_time; int write_pace_time; int write_strobe_time; int /*<<< orphan*/  data_width; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
struct nand_chip {int chip_delay; void* IO_ADDR_W; void* IO_ADDR_R; TYPE_2__ ecc; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  write_byte; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  cmd_ctrl; struct bcm2835_smi_nand_host* priv; } ;
struct TYPE_3__ {struct device* parent; } ;
struct mtd_info {int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/  owner; struct nand_chip* priv; } ;
struct device_node {int dummy; } ;
struct bcm2835_smi_nand_host {struct mtd_info mtd; struct nand_chip nand_chip; struct bcm2835_smi_instance* smi_inst; struct device* dev; } ;
struct bcm2835_smi_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_ECC_SOFT ; 
 int /*<<< orphan*/  SMI_WIDTH_8BIT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct bcm2835_smi_instance* bcm2835_smi_get (struct device_node*) ; 
 struct smi_settings* bcm2835_smi_get_settings_from_regs (struct bcm2835_smi_instance*) ; 
 int /*<<< orphan*/  bcm2835_smi_nand_cmd_ctrl ; 
 int /*<<< orphan*/  bcm2835_smi_nand_read_buf ; 
 int /*<<< orphan*/  bcm2835_smi_nand_read_byte ; 
 int /*<<< orphan*/  bcm2835_smi_nand_write_buf ; 
 int /*<<< orphan*/  bcm2835_smi_nand_write_byte ; 
 int /*<<< orphan*/  bcm2835_smi_set_regs_from_settings (struct bcm2835_smi_instance*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct bcm2835_smi_nand_host* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (struct mtd_info*) ; 
 scalar_t__ nand_scan (struct mtd_info*,int) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm2835_smi_nand_host*) ; 

__attribute__((used)) static int bcm2835_smi_nand_probe(struct platform_device *pdev)
{
	struct bcm2835_smi_nand_host *host;
	struct nand_chip *this;
	struct mtd_info *mtd;
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node, *smi_node;
	struct smi_settings *smi_settings;
	struct bcm2835_smi_instance *smi_inst;

	if (!node) {
		dev_err(dev, "No device tree node supplied!");
		return -EINVAL;
	}

	smi_node = of_parse_phandle(node, "smi_handle", 0);

	/* Request use of SMI peripheral: */
	smi_inst = bcm2835_smi_get(smi_node);

	if (!smi_inst) {
		dev_err(dev, "Could not register with SMI.");
		return -EPROBE_DEFER;
	}

	/* Set SMI timing and bus width */

	smi_settings = bcm2835_smi_get_settings_from_regs(smi_inst);

	smi_settings->data_width = SMI_WIDTH_8BIT;
	smi_settings->read_setup_time = 2;
	smi_settings->read_hold_time = 1;
	smi_settings->read_pace_time = 1;
	smi_settings->read_strobe_time = 3;

	smi_settings->write_setup_time = 2;
	smi_settings->write_hold_time = 1;
	smi_settings->write_pace_time = 1;
	smi_settings->write_strobe_time = 3;

	bcm2835_smi_set_regs_from_settings(smi_inst);

	host = devm_kzalloc(dev, sizeof(struct bcm2835_smi_nand_host),
		GFP_KERNEL);
	if (!host)
		return -ENOMEM;

	host->dev = dev;
	host->smi_inst = smi_inst;

	platform_set_drvdata(pdev, host);

	/* Link the structures together */

	this = &host->nand_chip;
	mtd = &host->mtd;
	mtd->priv = this;
	mtd->owner = THIS_MODULE;
	mtd->dev.parent = dev;
	mtd->name = DRIVER_NAME;

	/* 20 us command delay time... */
	this->chip_delay = 20;

	this->priv = host;
	this->cmd_ctrl = bcm2835_smi_nand_cmd_ctrl;
	this->read_byte = bcm2835_smi_nand_read_byte;
	this->write_byte = bcm2835_smi_nand_write_byte;
	this->write_buf = bcm2835_smi_nand_write_buf;
	this->read_buf = bcm2835_smi_nand_read_buf;

	this->ecc.mode = NAND_ECC_SOFT;

	/* Should never be accessed directly: */

	this->IO_ADDR_R = (void *)0xdeadbeef;
	this->IO_ADDR_W = (void *)0xdeadbeef;

	/* Scan to find the device and get the page size */

	if (nand_scan(mtd, 1))
		return -ENXIO;

	nand_release(mtd);
	return -EINVAL;
}