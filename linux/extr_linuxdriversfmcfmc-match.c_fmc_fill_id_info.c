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
struct fru_common_header {int format; } ;
struct fru_board_info_area {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  product_name; int /*<<< orphan*/  manufacturer; } ;
struct fmc_device {int /*<<< orphan*/ * eeprom; TYPE_1__ id; int /*<<< orphan*/  mezzanine_name; int /*<<< orphan*/  slot_id; int /*<<< orphan*/  hwdev; scalar_t__ eeprom_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int fmc_read_ee (struct fmc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fru_bia_cksum_ok (struct fru_board_info_area*) ; 
 struct fru_board_info_area* fru_get_board_area (struct fru_common_header*) ; 
 int /*<<< orphan*/  fru_get_board_manufacturer (struct fru_common_header*) ; 
 int /*<<< orphan*/  fru_get_product_name (struct fru_common_header*) ; 
 int /*<<< orphan*/  fru_header_cksum_ok (struct fru_common_header*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

int fmc_fill_id_info(struct fmc_device *fmc)
{
	struct fru_common_header *h;
	struct fru_board_info_area *bia;
	int ret, allocated = 0;

	/* If we know the eeprom length, try to read it off the device */
	if (fmc->eeprom_len && !fmc->eeprom) {
		fmc->eeprom = kzalloc(fmc->eeprom_len, GFP_KERNEL);
		if (!fmc->eeprom)
			return -ENOMEM;
		allocated = 1;
		ret = fmc_read_ee(fmc, 0, fmc->eeprom, fmc->eeprom_len);
		if (ret < 0)
			goto out;
	}

	/* If no eeprom, continue with other matches */
	if (!fmc->eeprom)
		return 0;

	dev_info(fmc->hwdev, "mezzanine %i\n", fmc->slot_id); /* header */

	/* So we have the eeprom: parse the FRU part (if any) */
	h = (void *)fmc->eeprom;
	if (h->format != 1) {
		pr_info("      EEPROM has no FRU information\n");
		goto out;
	}
	if (!fru_header_cksum_ok(h)) {
		pr_info("      FRU: wrong header checksum\n");
		goto out;
	}
	bia = fru_get_board_area(h);
	if (!fru_bia_cksum_ok(bia)) {
		pr_info("      FRU: wrong board area checksum\n");
		goto out;
	}
	fmc->id.manufacturer = fru_get_board_manufacturer(h);
	fmc->id.product_name = fru_get_product_name(h);
	pr_info("      Manufacturer: %s\n", fmc->id.manufacturer);
	pr_info("      Product name: %s\n", fmc->id.product_name);

	/* Create the short name (FIXME: look in sdb as well) */
	fmc->mezzanine_name = kstrdup(fmc->id.product_name, GFP_KERNEL);

out:
	if (allocated) {
		kfree(fmc->eeprom);
		fmc->eeprom = NULL;
	}
	return 0; /* no error: let other identification work */
}