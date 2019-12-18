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
struct nand_flash_dev {int dummy; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int nand_attach (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_detach (struct nand_chip*) ; 
 int nand_scan_ident (struct nand_chip*,unsigned int,struct nand_flash_dev*) ; 
 int /*<<< orphan*/  nand_scan_ident_cleanup (struct nand_chip*) ; 
 int nand_scan_tail (struct nand_chip*) ; 

int nand_scan_with_ids(struct nand_chip *chip, unsigned int maxchips,
		       struct nand_flash_dev *ids)
{
	int ret;

	if (!maxchips)
		return -EINVAL;

	ret = nand_scan_ident(chip, maxchips, ids);
	if (ret)
		return ret;

	ret = nand_attach(chip);
	if (ret)
		goto cleanup_ident;

	ret = nand_scan_tail(chip);
	if (ret)
		goto detach_chip;

	return 0;

detach_chip:
	nand_detach(chip);
cleanup_ident:
	nand_scan_ident_cleanup(chip);

	return ret;
}