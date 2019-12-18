#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_10__ {int options; int bytes; void* strength; void* size; int /*<<< orphan*/  algo; } ;
struct TYPE_8__ {void* step_size; void* strength; } ;
struct TYPE_9__ {TYPE_2__ eccreq; } ;
struct nand_chip {int /*<<< orphan*/  options; TYPE_4__ ecc; TYPE_3__ base; int /*<<< orphan*/  controller; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct TYPE_11__ {int bytes; int nsectors; void* strength; void* sectorsize; scalar_t__ ooboffset; } ;
struct atmel_pmecc_user_req {int pagesize; int oobsize; TYPE_5__ ecc; } ;
struct atmel_nand_controller {int /*<<< orphan*/  pmecc; TYPE_6__* dev; TYPE_1__* caps; } ;
struct atmel_nand {int /*<<< orphan*/  pmecc; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_7__ {scalar_t__ legacy_of_bindings; } ;

/* Variables and functions */
 void* ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH ; 
 scalar_t__ ATMEL_PMECC_OOBOFFSET_AUTO ; 
 void* ATMEL_PMECC_SECTOR_SIZE_AUTO ; 
 int ENOTSUPP ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAND_ECC_BCH ; 
 int NAND_ECC_MAXIMIZE ; 
 int /*<<< orphan*/  NAND_NO_SUBPAGE_WRITE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_pmecc_create_user (int /*<<< orphan*/ ,struct atmel_pmecc_user_req*) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_ooblayout_lp_ops ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,void**) ; 
 struct atmel_nand* to_atmel_nand (struct nand_chip*) ; 
 struct atmel_nand_controller* to_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_nand_pmecc_init(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct atmel_nand *nand = to_atmel_nand(chip);
	struct atmel_nand_controller *nc;
	struct atmel_pmecc_user_req req;

	nc = to_nand_controller(chip->controller);

	if (!nc->pmecc) {
		dev_err(nc->dev, "HW ECC not supported\n");
		return -ENOTSUPP;
	}

	if (nc->caps->legacy_of_bindings) {
		u32 val;

		if (!of_property_read_u32(nc->dev->of_node, "atmel,pmecc-cap",
					  &val))
			chip->ecc.strength = val;

		if (!of_property_read_u32(nc->dev->of_node,
					  "atmel,pmecc-sector-size",
					  &val))
			chip->ecc.size = val;
	}

	if (chip->ecc.options & NAND_ECC_MAXIMIZE)
		req.ecc.strength = ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH;
	else if (chip->ecc.strength)
		req.ecc.strength = chip->ecc.strength;
	else if (chip->base.eccreq.strength)
		req.ecc.strength = chip->base.eccreq.strength;
	else
		req.ecc.strength = ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH;

	if (chip->ecc.size)
		req.ecc.sectorsize = chip->ecc.size;
	else if (chip->base.eccreq.step_size)
		req.ecc.sectorsize = chip->base.eccreq.step_size;
	else
		req.ecc.sectorsize = ATMEL_PMECC_SECTOR_SIZE_AUTO;

	req.pagesize = mtd->writesize;
	req.oobsize = mtd->oobsize;

	if (mtd->writesize <= 512) {
		req.ecc.bytes = 4;
		req.ecc.ooboffset = 0;
	} else {
		req.ecc.bytes = mtd->oobsize - 2;
		req.ecc.ooboffset = ATMEL_PMECC_OOBOFFSET_AUTO;
	}

	nand->pmecc = atmel_pmecc_create_user(nc->pmecc, &req);
	if (IS_ERR(nand->pmecc))
		return PTR_ERR(nand->pmecc);

	chip->ecc.algo = NAND_ECC_BCH;
	chip->ecc.size = req.ecc.sectorsize;
	chip->ecc.bytes = req.ecc.bytes / req.ecc.nsectors;
	chip->ecc.strength = req.ecc.strength;

	chip->options |= NAND_NO_SUBPAGE_WRITE;

	mtd_set_ooblayout(mtd, &nand_ooblayout_lp_ops);

	return 0;
}