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
struct nand_chip {int /*<<< orphan*/  (* select_chip ) (struct mtd_info*,int) ;int /*<<< orphan*/  (* read_buf ) (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * data_buf; } ;
struct mtd_info {int dummy; } ;
struct boot_rom_geometry {int search_area_stride_exponent; unsigned int stride_size_in_pages; } ;
struct gpmi_nand_data {int current_chip; struct nand_chip nand; struct device* dev; struct boot_rom_geometry rom_geometry; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  fingerprint ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,unsigned int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int) ; 

__attribute__((used)) static int mx23_check_transcription_stamp(struct gpmi_nand_data *this)
{
	struct boot_rom_geometry *rom_geo = &this->rom_geometry;
	struct device *dev = this->dev;
	struct nand_chip *chip = &this->nand;
	struct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int search_area_size_in_strides;
	unsigned int stride;
	unsigned int page;
	uint8_t *buffer = chip->data_buf;
	int saved_chip_number;
	int found_an_ncb_fingerprint = false;

	/* Compute the number of strides in a search area. */
	search_area_size_in_strides = 1 << rom_geo->search_area_stride_exponent;

	saved_chip_number = this->current_chip;
	chip->select_chip(mtd, 0);

	/*
	 * Loop through the first search area, looking for the NCB fingerprint.
	 */
	dev_dbg(dev, "Scanning for an NCB fingerprint...\n");

	for (stride = 0; stride < search_area_size_in_strides; stride++) {
		/* Compute the page addresses. */
		page = stride * rom_geo->stride_size_in_pages;

		dev_dbg(dev, "Looking for a fingerprint in page 0x%x\n", page);

		/*
		 * Read the NCB fingerprint. The fingerprint is four bytes long
		 * and starts in the 12th byte of the page.
		 */
		nand_read_page_op(chip, page, 12, NULL, 0);
		chip->read_buf(mtd, buffer, strlen(fingerprint));

		/* Look for the fingerprint. */
		if (!memcmp(buffer, fingerprint, strlen(fingerprint))) {
			found_an_ncb_fingerprint = true;
			break;
		}

	}

	chip->select_chip(mtd, saved_chip_number);

	if (found_an_ncb_fingerprint)
		dev_dbg(dev, "\tFound a fingerprint\n");
	else
		dev_dbg(dev, "\tNo fingerprint found\n");
	return found_an_ncb_fingerprint;
}