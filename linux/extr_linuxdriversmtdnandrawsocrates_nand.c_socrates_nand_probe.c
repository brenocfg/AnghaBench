#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  algo; int /*<<< orphan*/  mode; } ;
struct nand_chip {int chip_delay; TYPE_2__ ecc; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_word; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  cmd_ctrl; void* IO_ADDR_W; void* IO_ADDR_R; } ;
struct socrates_nand_host {int /*<<< orphan*/ * io_base; TYPE_3__* dev; struct nand_chip nand_chip; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_6__ {TYPE_3__* parent; } ;
struct mtd_info {char* name; TYPE_1__ dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_ECC_HAMMING ; 
 int /*<<< orphan*/  NAND_ECC_SOFT ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_3__*,struct socrates_nand_host*) ; 
 struct socrates_nand_host* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (struct mtd_info*) ; 
 int nand_scan (struct mtd_info*,int) ; 
 int /*<<< orphan*/  nand_set_controller_data (struct nand_chip*,struct socrates_nand_host*) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/ * of_iomap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socrates_nand_cmd_ctrl ; 
 int /*<<< orphan*/  socrates_nand_device_ready ; 
 int /*<<< orphan*/  socrates_nand_read_buf ; 
 int /*<<< orphan*/  socrates_nand_read_byte ; 
 int /*<<< orphan*/  socrates_nand_read_word ; 
 int /*<<< orphan*/  socrates_nand_write_buf ; 

__attribute__((used)) static int socrates_nand_probe(struct platform_device *ofdev)
{
	struct socrates_nand_host *host;
	struct mtd_info *mtd;
	struct nand_chip *nand_chip;
	int res;

	/* Allocate memory for the device structure (and zero it) */
	host = devm_kzalloc(&ofdev->dev, sizeof(*host), GFP_KERNEL);
	if (!host)
		return -ENOMEM;

	host->io_base = of_iomap(ofdev->dev.of_node, 0);
	if (host->io_base == NULL) {
		dev_err(&ofdev->dev, "ioremap failed\n");
		return -EIO;
	}

	nand_chip = &host->nand_chip;
	mtd = nand_to_mtd(nand_chip);
	host->dev = &ofdev->dev;

	/* link the private data structures */
	nand_set_controller_data(nand_chip, host);
	nand_set_flash_node(nand_chip, ofdev->dev.of_node);
	mtd->name = "socrates_nand";
	mtd->dev.parent = &ofdev->dev;

	/*should never be accessed directly */
	nand_chip->IO_ADDR_R = (void *)0xdeadbeef;
	nand_chip->IO_ADDR_W = (void *)0xdeadbeef;

	nand_chip->cmd_ctrl = socrates_nand_cmd_ctrl;
	nand_chip->read_byte = socrates_nand_read_byte;
	nand_chip->read_word = socrates_nand_read_word;
	nand_chip->write_buf = socrates_nand_write_buf;
	nand_chip->read_buf = socrates_nand_read_buf;
	nand_chip->dev_ready = socrates_nand_device_ready;

	nand_chip->ecc.mode = NAND_ECC_SOFT;	/* enable ECC */
	nand_chip->ecc.algo = NAND_ECC_HAMMING;

	/* TODO: I have no idea what real delay is. */
	nand_chip->chip_delay = 20;		/* 20us command delay time */

	dev_set_drvdata(&ofdev->dev, host);

	res = nand_scan(mtd, 1);
	if (res)
		goto out;

	res = mtd_device_register(mtd, NULL, 0);
	if (!res)
		return res;

	nand_release(mtd);

out:
	iounmap(host->io_base);
	return res;
}