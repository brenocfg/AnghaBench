#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ mode; int bytes; int size; int strength; int /*<<< orphan*/  write_page_raw; int /*<<< orphan*/  read_page_raw; int /*<<< orphan*/  write_page; int /*<<< orphan*/  read_page; int /*<<< orphan*/  algo; } ;
struct TYPE_5__ {int strength; } ;
struct TYPE_6__ {TYPE_1__ eccreq; } ;
struct nand_chip {int options; TYPE_3__ ecc; TYPE_2__ base; } ;
struct mtd_info {int writesize; scalar_t__ oobsize; } ;
struct TYPE_8__ {int forced; int enabled; struct micron_nand* rawbuf; } ;
struct micron_nand {TYPE_4__ ecc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MICRON_ON_DIE_MANDATORY ; 
 int MICRON_ON_DIE_UNSUPPORTED ; 
 int NAND_BBM_FIRSTPAGE ; 
 int NAND_BBM_SECONDPAGE ; 
 int /*<<< orphan*/  NAND_ECC_BCH ; 
 scalar_t__ NAND_ECC_ON_DIE ; 
 int /*<<< orphan*/  kfree (struct micron_nand*) ; 
 struct micron_nand* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct micron_nand* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  micron_nand_on_die_4_ooblayout_ops ; 
 int /*<<< orphan*/  micron_nand_on_die_8_ooblayout_ops ; 
 int micron_nand_onfi_init (struct nand_chip*) ; 
 int /*<<< orphan*/  micron_nand_read_page_on_die_ecc ; 
 int /*<<< orphan*/  micron_nand_write_page_on_die_ecc ; 
 int micron_supports_on_die_ecc (struct nand_chip*) ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_read_page_raw ; 
 int /*<<< orphan*/  nand_read_page_raw_notsupp ; 
 int /*<<< orphan*/  nand_set_manufacturer_data (struct nand_chip*,struct micron_nand*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_write_page_raw ; 
 int /*<<< orphan*/  nand_write_page_raw_notsupp ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int micron_nand_init(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct micron_nand *micron;
	int ondie;
	int ret;

	micron = kzalloc(sizeof(*micron), GFP_KERNEL);
	if (!micron)
		return -ENOMEM;

	nand_set_manufacturer_data(chip, micron);

	ret = micron_nand_onfi_init(chip);
	if (ret)
		goto err_free_manuf_data;

	if (mtd->writesize == 2048)
		chip->options |= NAND_BBM_FIRSTPAGE | NAND_BBM_SECONDPAGE;

	ondie = micron_supports_on_die_ecc(chip);

	if (ondie == MICRON_ON_DIE_MANDATORY &&
	    chip->ecc.mode != NAND_ECC_ON_DIE) {
		pr_err("On-die ECC forcefully enabled, not supported\n");
		ret = -EINVAL;
		goto err_free_manuf_data;
	}

	if (chip->ecc.mode == NAND_ECC_ON_DIE) {
		if (ondie == MICRON_ON_DIE_UNSUPPORTED) {
			pr_err("On-die ECC selected but not supported\n");
			ret = -EINVAL;
			goto err_free_manuf_data;
		}

		if (ondie == MICRON_ON_DIE_MANDATORY) {
			micron->ecc.forced = true;
			micron->ecc.enabled = true;
		}

		/*
		 * In case of 4bit on-die ECC, we need a buffer to store a
		 * page dumped in raw mode so that we can compare its content
		 * to the same page after ECC correction happened and extract
		 * the real number of bitflips from this comparison.
		 * That's not needed for 8-bit ECC, because the status expose
		 * a better approximation of the number of bitflips in a page.
		 */
		if (chip->base.eccreq.strength == 4) {
			micron->ecc.rawbuf = kmalloc(mtd->writesize +
						     mtd->oobsize,
						     GFP_KERNEL);
			if (!micron->ecc.rawbuf) {
				ret = -ENOMEM;
				goto err_free_manuf_data;
			}
		}

		if (chip->base.eccreq.strength == 4)
			mtd_set_ooblayout(mtd,
					  &micron_nand_on_die_4_ooblayout_ops);
		else
			mtd_set_ooblayout(mtd,
					  &micron_nand_on_die_8_ooblayout_ops);

		chip->ecc.bytes = chip->base.eccreq.strength * 2;
		chip->ecc.size = 512;
		chip->ecc.strength = chip->base.eccreq.strength;
		chip->ecc.algo = NAND_ECC_BCH;
		chip->ecc.read_page = micron_nand_read_page_on_die_ecc;
		chip->ecc.write_page = micron_nand_write_page_on_die_ecc;

		if (ondie == MICRON_ON_DIE_MANDATORY) {
			chip->ecc.read_page_raw = nand_read_page_raw_notsupp;
			chip->ecc.write_page_raw = nand_write_page_raw_notsupp;
		} else {
			chip->ecc.read_page_raw = nand_read_page_raw;
			chip->ecc.write_page_raw = nand_write_page_raw;
		}
	}

	return 0;

err_free_manuf_data:
	kfree(micron->ecc.rawbuf);
	kfree(micron);

	return ret;
}