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
typedef  int u8 ;
typedef  int u32 ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct bcma_drv_cc {int dummy; } ;
struct bcm47xxnflash {int curr_command; int curr_column; int* id_data; struct bcma_drv_cc* cc; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BCMA_CC_NFLASH_DATA ; 
#define  NAND_CMD_READID 130 
#define  NAND_CMD_READOOB 129 
#define  NAND_CMD_STATUS 128 
 int /*<<< orphan*/  NCTL_READ ; 
 int /*<<< orphan*/  bcm47xxnflash_ops_bcm4706_ctl_cmd (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm47xxnflash_ops_bcm4706_read (struct mtd_info*,int*,int) ; 
 int bcma_cc_read32 (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 
 struct bcm47xxnflash* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static u8 bcm47xxnflash_ops_bcm4706_read_byte(struct nand_chip *nand_chip)
{
	struct mtd_info *mtd = nand_to_mtd(nand_chip);
	struct bcm47xxnflash *b47n = nand_get_controller_data(nand_chip);
	struct bcma_drv_cc *cc = b47n->cc;
	u32 tmp = 0;

	switch (b47n->curr_command) {
	case NAND_CMD_READID:
		if (b47n->curr_column >= ARRAY_SIZE(b47n->id_data)) {
			pr_err("Requested invalid id_data: %d\n",
			       b47n->curr_column);
			return 0;
		}
		return b47n->id_data[b47n->curr_column++];
	case NAND_CMD_STATUS:
		if (bcm47xxnflash_ops_bcm4706_ctl_cmd(cc, NCTL_READ))
			return 0;
		return bcma_cc_read32(cc, BCMA_CC_NFLASH_DATA) & 0xff;
	case NAND_CMD_READOOB:
		bcm47xxnflash_ops_bcm4706_read(mtd, (u8 *)&tmp, 4);
		return tmp & 0xFF;
	}

	pr_err("Invalid command for byte read: 0x%X\n", b47n->curr_command);
	return 0;
}