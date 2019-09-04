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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct hinfc_host {scalar_t__ command; int mmio; int offset; int buffer; } ;

/* Variables and functions */
 scalar_t__ NAND_CMD_READID ; 
 scalar_t__ NAND_CMD_STATUS ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct hinfc_host* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static uint8_t hisi_nfc_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hinfc_host *host = nand_get_controller_data(chip);

	if (host->command == NAND_CMD_STATUS)
		return *(uint8_t *)(host->mmio);

	host->offset++;

	if (host->command == NAND_CMD_READID)
		return *(uint8_t *)(host->mmio + host->offset - 1);

	return *(uint8_t *)(host->buffer + host->offset - 1);
}