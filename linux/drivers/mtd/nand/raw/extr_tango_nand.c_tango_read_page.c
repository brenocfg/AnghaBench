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
typedef  int /*<<< orphan*/  u8 ;
struct tango_nfc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_oob_raw ) (struct nand_chip*,int) ;int /*<<< orphan*/  (* read_oob ) (struct nand_chip*,int) ;} ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/  controller; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  NFC_READ ; 
 int check_erased_page (struct nand_chip*,int /*<<< orphan*/ *) ; 
 int decode_error_report (struct nand_chip*) ; 
 int do_dma (struct tango_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int) ; 
 int /*<<< orphan*/  stub2 (struct nand_chip*,int) ; 
 struct tango_nfc* to_tango_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tango_read_page(struct nand_chip *chip, u8 *buf,
			   int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct tango_nfc *nfc = to_tango_nfc(chip->controller);
	int err, res, len = mtd->writesize;

	if (oob_required)
		chip->ecc.read_oob(chip, page);

	err = do_dma(nfc, DMA_FROM_DEVICE, NFC_READ, buf, len, page);
	if (err)
		return err;

	res = decode_error_report(chip);
	if (res < 0) {
		chip->ecc.read_oob_raw(chip, page);
		res = check_erased_page(chip, buf);
	}

	return res;
}