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
struct bcm47xxnflash {int curr_command; } ;

/* Variables and functions */
#define  NAND_CMD_SEQIN 128 
 int /*<<< orphan*/  bcm47xxnflash_ops_bcm4706_write (struct mtd_info*,int /*<<< orphan*/  const*,int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct bcm47xxnflash* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void bcm47xxnflash_ops_bcm4706_write_buf(struct mtd_info *mtd,
						const uint8_t *buf, int len)
{
	struct nand_chip *nand_chip = mtd_to_nand(mtd);
	struct bcm47xxnflash *b47n = nand_get_controller_data(nand_chip);

	switch (b47n->curr_command) {
	case NAND_CMD_SEQIN:
		bcm47xxnflash_ops_bcm4706_write(mtd, buf, len);
		return;
	}

	pr_err("Invalid command for buf write: 0x%X\n", b47n->curr_command);
}