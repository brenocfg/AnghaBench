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
typedef  int /*<<< orphan*/  u8 ;
struct vf610_nfc {int data_access; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct vf610_nfc* mtd_to_nfc (struct mtd_info*) ; 
 int nand_read_page_raw (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int vf610_nfc_read_page_raw(struct mtd_info *mtd,
				   struct nand_chip *chip, u8 *buf,
				   int oob_required, int page)
{
	struct vf610_nfc *nfc = mtd_to_nfc(mtd);
	int ret;

	nfc->data_access = true;
	ret = nand_read_page_raw(mtd, chip, buf, oob_required, page);
	nfc->data_access = false;

	return ret;
}