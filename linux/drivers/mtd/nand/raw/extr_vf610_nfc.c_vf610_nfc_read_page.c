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
typedef  int u32 ;
struct vf610_nfc {scalar_t__ regs; int /*<<< orphan*/  ecc_mode; } ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; int /*<<< orphan*/  cur_cs; } ;
struct TYPE_2__ {int corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {int writesize; int oobsize; TYPE_1__ ecc_stats; } ;

/* Variables and functions */
 int CMD_BYTE1_SHIFT ; 
 int CMD_BYTE2_SHIFT ; 
 int CMD_CODE_SHIFT ; 
 int COMMAND_CAR_BYTE1 ; 
 int COMMAND_CAR_BYTE2 ; 
 int COMMAND_CMD_BYTE1 ; 
 int COMMAND_CMD_BYTE2 ; 
 int COMMAND_RB_HANDSHAKE ; 
 int COMMAND_READ_DATA ; 
 int /*<<< orphan*/  ECC_BYPASS ; 
 int NAND_CMD_READ0 ; 
 int NAND_CMD_READSTART ; 
 scalar_t__ NFC_MAIN_AREA (int /*<<< orphan*/ ) ; 
 struct vf610_nfc* chip_to_nfc (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int vf610_nfc_correct_data (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vf610_nfc_ecc_mode (struct vf610_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf610_nfc_fill_row (struct nand_chip*,int,int*,int*) ; 
 int /*<<< orphan*/  vf610_nfc_rd_from_sram (int /*<<< orphan*/ *,scalar_t__,int,int) ; 
 int /*<<< orphan*/  vf610_nfc_run (struct vf610_nfc*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  vf610_nfc_select_target (struct nand_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vf610_nfc_read_page(struct nand_chip *chip, uint8_t *buf,
			       int oob_required, int page)
{
	struct vf610_nfc *nfc = chip_to_nfc(chip);
	struct mtd_info *mtd = nand_to_mtd(chip);
	int trfr_sz = mtd->writesize + mtd->oobsize;
	u32 row = 0, cmd1 = 0, cmd2 = 0, code = 0;
	int stat;

	vf610_nfc_select_target(chip, chip->cur_cs);

	cmd2 |= NAND_CMD_READ0 << CMD_BYTE1_SHIFT;
	code |= COMMAND_CMD_BYTE1 | COMMAND_CAR_BYTE1 | COMMAND_CAR_BYTE2;

	vf610_nfc_fill_row(chip, page, &code, &row);

	cmd1 |= NAND_CMD_READSTART << CMD_BYTE2_SHIFT;
	code |= COMMAND_CMD_BYTE2 | COMMAND_RB_HANDSHAKE | COMMAND_READ_DATA;

	cmd2 |= code << CMD_CODE_SHIFT;

	vf610_nfc_ecc_mode(nfc, nfc->ecc_mode);
	vf610_nfc_run(nfc, 0, row, cmd1, cmd2, trfr_sz);
	vf610_nfc_ecc_mode(nfc, ECC_BYPASS);

	/*
	 * Don't fix endianness on page access for historical reasons.
	 * See comment in vf610_nfc_rd_from_sram
	 */
	vf610_nfc_rd_from_sram(buf, nfc->regs + NFC_MAIN_AREA(0),
			       mtd->writesize, false);
	if (oob_required)
		vf610_nfc_rd_from_sram(chip->oob_poi,
				       nfc->regs + NFC_MAIN_AREA(0) +
						   mtd->writesize,
				       mtd->oobsize, false);

	stat = vf610_nfc_correct_data(chip, buf, chip->oob_poi, page);

	if (stat < 0) {
		mtd->ecc_stats.failed++;
		return 0;
	} else {
		mtd->ecc_stats.corrected += stat;
		return stat;
	}
}