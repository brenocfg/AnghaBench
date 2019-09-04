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
struct nand_chip {int dummy; } ;
struct hynix_nand {struct hynix_nand* read_retry; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hynix_nand*) ; 
 struct hynix_nand* nand_get_manufacturer_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_set_manufacturer_data (struct nand_chip*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hynix_nand_cleanup(struct nand_chip *chip)
{
	struct hynix_nand *hynix = nand_get_manufacturer_data(chip);

	if (!hynix)
		return;

	kfree(hynix->read_retry);
	kfree(hynix);
	nand_set_manufacturer_data(chip, NULL);
}