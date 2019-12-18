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
struct vf610_nfc {int data_access; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 struct vf610_nfc* chip_to_nfc (struct nand_chip*) ; 
 int nand_read_oob_std (struct nand_chip*,int) ; 

__attribute__((used)) static int vf610_nfc_read_oob(struct nand_chip *chip, int page)
{
	struct vf610_nfc *nfc = chip_to_nfc(chip);
	int ret;

	nfc->data_access = true;
	ret = nand_read_oob_std(chip, page);
	nfc->data_access = false;

	return ret;
}