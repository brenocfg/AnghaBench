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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int /*<<< orphan*/  const* oob_poi; } ;
struct mtd_info {int /*<<< orphan*/  writesize; int /*<<< orphan*/  oobsize; } ;
struct bch_geometry {int /*<<< orphan*/  payload_size; int /*<<< orphan*/  auxiliary_size; } ;
struct gpmi_nand_data {void* payload_virt; void* auxiliary_virt; int /*<<< orphan*/  payload_phys; int /*<<< orphan*/  auxiliary_phys; scalar_t__ swap_block_mark; int /*<<< orphan*/  dev; struct bch_geometry bch_geometry; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_mark_swapping (struct gpmi_nand_data*,void*,void*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int gpmi_send_page (struct gpmi_nand_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct gpmi_nand_data* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 int /*<<< orphan*/  send_page_end (struct gpmi_nand_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int send_page_prepare (struct gpmi_nand_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpmi_ecc_write_page(struct mtd_info *mtd, struct nand_chip *chip,
				const uint8_t *buf, int oob_required, int page)
{
	struct gpmi_nand_data *this = nand_get_controller_data(chip);
	struct bch_geometry *nfc_geo = &this->bch_geometry;
	const void *payload_virt;
	dma_addr_t payload_phys;
	const void *auxiliary_virt;
	dma_addr_t auxiliary_phys;
	int        ret;

	dev_dbg(this->dev, "ecc write page.\n");

	nand_prog_page_begin_op(chip, page, 0, NULL, 0);

	if (this->swap_block_mark) {
		/*
		 * If control arrives here, we're doing block mark swapping.
		 * Since we can't modify the caller's buffers, we must copy them
		 * into our own.
		 */
		memcpy(this->payload_virt, buf, mtd->writesize);
		payload_virt = this->payload_virt;
		payload_phys = this->payload_phys;

		memcpy(this->auxiliary_virt, chip->oob_poi,
				nfc_geo->auxiliary_size);
		auxiliary_virt = this->auxiliary_virt;
		auxiliary_phys = this->auxiliary_phys;

		/* Handle block mark swapping. */
		block_mark_swapping(this,
				(void *)payload_virt, (void *)auxiliary_virt);
	} else {
		/*
		 * If control arrives here, we're not doing block mark swapping,
		 * so we can to try and use the caller's buffers.
		 */
		ret = send_page_prepare(this,
				buf, mtd->writesize,
				this->payload_virt, this->payload_phys,
				nfc_geo->payload_size,
				&payload_virt, &payload_phys);
		if (ret) {
			dev_err(this->dev, "Inadequate payload DMA buffer\n");
			return 0;
		}

		ret = send_page_prepare(this,
				chip->oob_poi, mtd->oobsize,
				this->auxiliary_virt, this->auxiliary_phys,
				nfc_geo->auxiliary_size,
				&auxiliary_virt, &auxiliary_phys);
		if (ret) {
			dev_err(this->dev, "Inadequate auxiliary DMA buffer\n");
			goto exit_auxiliary;
		}
	}

	/* Ask the NFC. */
	ret = gpmi_send_page(this, payload_phys, auxiliary_phys);
	if (ret)
		dev_err(this->dev, "Error in ECC-based write: %d\n", ret);

	if (!this->swap_block_mark) {
		send_page_end(this, chip->oob_poi, mtd->oobsize,
				this->auxiliary_virt, this->auxiliary_phys,
				nfc_geo->auxiliary_size,
				auxiliary_virt, auxiliary_phys);
exit_auxiliary:
		send_page_end(this, buf, mtd->writesize,
				this->payload_virt, this->payload_phys,
				nfc_geo->payload_size,
				payload_virt, payload_phys);
	}

	if (ret)
		return ret;

	return nand_prog_page_end_op(chip);
}