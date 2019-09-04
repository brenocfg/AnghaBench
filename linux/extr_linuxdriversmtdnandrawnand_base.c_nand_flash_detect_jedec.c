#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct nand_jedec_params {int lun_count; struct jedec_ecc_info* ecc_info; int /*<<< orphan*/  features; int /*<<< orphan*/  bits_per_cell; int /*<<< orphan*/  blocks_per_lun; int /*<<< orphan*/  spare_bytes_per_page; int /*<<< orphan*/  pages_per_block; int /*<<< orphan*/  byte_per_page; int /*<<< orphan*/  model; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  revision; int /*<<< orphan*/  crc; } ;
struct TYPE_2__ {int /*<<< orphan*/  model; } ;
struct nand_chip {int chipsize; int ecc_step_ds; int /*<<< orphan*/  ecc_strength_ds; int /*<<< orphan*/  options; int /*<<< orphan*/  bits_per_cell; TYPE_1__ parameters; } ;
struct mtd_info {int writesize; int erasesize; int oobsize; } ;
struct jedec_ecc_info {int codeword_size; int /*<<< orphan*/  ecc_bits; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int JEDEC_FEATURE_16_BIT_BUS ; 
 int /*<<< orphan*/  NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  ONFI_CRC_BASE ; 
 int fls (int) ; 
 int /*<<< orphan*/  kfree (struct nand_jedec_params*) ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nand_jedec_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int nand_read_data_op (struct nand_chip*,struct nand_jedec_params*,int,int) ; 
 int nand_read_param_page_op (struct nand_chip*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_readid_op (struct nand_chip*,int,char*,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int onfi_crc16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  sanitize_string (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int nand_flash_detect_jedec(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct nand_jedec_params *p;
	struct jedec_ecc_info *ecc;
	int jedec_version = 0;
	char id[5];
	int i, val, ret;

	/* Try JEDEC for unknown chip or LP */
	ret = nand_readid_op(chip, 0x40, id, sizeof(id));
	if (ret || strncmp(id, "JEDEC", sizeof(id)))
		return 0;

	/* JEDEC chip: allocate a buffer to hold its parameter page */
	p = kzalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	ret = nand_read_param_page_op(chip, 0x40, NULL, 0);
	if (ret) {
		ret = 0;
		goto free_jedec_param_page;
	}

	for (i = 0; i < 3; i++) {
		ret = nand_read_data_op(chip, p, sizeof(*p), true);
		if (ret) {
			ret = 0;
			goto free_jedec_param_page;
		}

		if (onfi_crc16(ONFI_CRC_BASE, (uint8_t *)p, 510) ==
				le16_to_cpu(p->crc))
			break;
	}

	if (i == 3) {
		pr_err("Could not find valid JEDEC parameter page; aborting\n");
		goto free_jedec_param_page;
	}

	/* Check version */
	val = le16_to_cpu(p->revision);
	if (val & (1 << 2))
		jedec_version = 10;
	else if (val & (1 << 1))
		jedec_version = 1; /* vendor specific version */

	if (!jedec_version) {
		pr_info("unsupported JEDEC version: %d\n", val);
		goto free_jedec_param_page;
	}

	sanitize_string(p->manufacturer, sizeof(p->manufacturer));
	sanitize_string(p->model, sizeof(p->model));
	chip->parameters.model = kstrdup(p->model, GFP_KERNEL);
	if (!chip->parameters.model) {
		ret = -ENOMEM;
		goto free_jedec_param_page;
	}

	mtd->writesize = le32_to_cpu(p->byte_per_page);

	/* Please reference to the comment for nand_flash_detect_onfi. */
	mtd->erasesize = 1 << (fls(le32_to_cpu(p->pages_per_block)) - 1);
	mtd->erasesize *= mtd->writesize;

	mtd->oobsize = le16_to_cpu(p->spare_bytes_per_page);

	/* Please reference to the comment for nand_flash_detect_onfi. */
	chip->chipsize = 1 << (fls(le32_to_cpu(p->blocks_per_lun)) - 1);
	chip->chipsize *= (uint64_t)mtd->erasesize * p->lun_count;
	chip->bits_per_cell = p->bits_per_cell;

	if (le16_to_cpu(p->features) & JEDEC_FEATURE_16_BIT_BUS)
		chip->options |= NAND_BUSWIDTH_16;

	/* ECC info */
	ecc = &p->ecc_info[0];

	if (ecc->codeword_size >= 9) {
		chip->ecc_strength_ds = ecc->ecc_bits;
		chip->ecc_step_ds = 1 << ecc->codeword_size;
	} else {
		pr_warn("Invalid codeword size\n");
	}

free_jedec_param_page:
	kfree(p);
	return ret;
}