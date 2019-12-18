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
typedef  int uint ;
struct nand_chip {int /*<<< orphan*/  options; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct mpc512x_reset_module {int /*<<< orphan*/  rcwhr; } ;
struct mpc5121_nfc_prv {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (struct mpc512x_reset_module*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mpc5121_nfc_prv* nand_get_controller_data (struct nand_chip*) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct mpc512x_reset_module* of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int mpc5121_nfc_read_hw_config(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mpc5121_nfc_prv *prv = nand_get_controller_data(chip);
	struct mpc512x_reset_module *rm;
	struct device_node *rmnode;
	uint rcw_pagesize = 0;
	uint rcw_sparesize = 0;
	uint rcw_width;
	uint rcwh;
	uint romloc, ps;
	int ret = 0;

	rmnode = of_find_compatible_node(NULL, NULL, "fsl,mpc5121-reset");
	if (!rmnode) {
		dev_err(prv->dev, "Missing 'fsl,mpc5121-reset' "
					"node in device tree!\n");
		return -ENODEV;
	}

	rm = of_iomap(rmnode, 0);
	if (!rm) {
		dev_err(prv->dev, "Error mapping reset module node!\n");
		ret = -EBUSY;
		goto out;
	}

	rcwh = in_be32(&rm->rcwhr);

	/* Bit 6: NFC bus width */
	rcw_width = ((rcwh >> 6) & 0x1) ? 2 : 1;

	/* Bit 7: NFC Page/Spare size */
	ps = (rcwh >> 7) & 0x1;

	/* Bits [22:21]: ROM Location */
	romloc = (rcwh >> 21) & 0x3;

	/* Decode RCW bits */
	switch ((ps << 2) | romloc) {
	case 0x00:
	case 0x01:
		rcw_pagesize = 512;
		rcw_sparesize = 16;
		break;
	case 0x02:
	case 0x03:
		rcw_pagesize = 4096;
		rcw_sparesize = 128;
		break;
	case 0x04:
	case 0x05:
		rcw_pagesize = 2048;
		rcw_sparesize = 64;
		break;
	case 0x06:
	case 0x07:
		rcw_pagesize = 4096;
		rcw_sparesize = 218;
		break;
	}

	mtd->writesize = rcw_pagesize;
	mtd->oobsize = rcw_sparesize;
	if (rcw_width == 2)
		chip->options |= NAND_BUSWIDTH_16;

	dev_notice(prv->dev, "Configured for "
				"%u-bit NAND, page size %u "
				"with %u spare.\n",
				rcw_width * 8, rcw_pagesize,
				rcw_sparesize);
	iounmap(rm);
out:
	of_node_put(rmnode);
	return ret;
}