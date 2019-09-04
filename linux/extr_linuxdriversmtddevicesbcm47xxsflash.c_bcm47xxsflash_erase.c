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
struct mtd_info {struct bcm47xxsflash* priv; } ;
struct erase_info {int addr; } ;
struct bcm47xxsflash {int type; int blocksize; int /*<<< orphan*/  (* cc_write ) (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
#define  BCM47XXSFLASH_TYPE_ATMEL 129 
#define  BCM47XXSFLASH_TYPE_ST 128 
 int /*<<< orphan*/  BCMA_CC_FLASHADDR ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  OPCODE_AT_PAGE_ERASE ; 
 int /*<<< orphan*/  OPCODE_ST_SE ; 
 int /*<<< orphan*/  OPCODE_ST_SSE ; 
 int /*<<< orphan*/  OPCODE_ST_WREN ; 
 int /*<<< orphan*/  bcm47xxsflash_cmd (struct bcm47xxsflash*,int /*<<< orphan*/ ) ; 
 int bcm47xxsflash_poll (struct bcm47xxsflash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm47xxsflash_erase(struct mtd_info *mtd, struct erase_info *erase)
{
	struct bcm47xxsflash *b47s = mtd->priv;

	switch (b47s->type) {
	case BCM47XXSFLASH_TYPE_ST:
		bcm47xxsflash_cmd(b47s, OPCODE_ST_WREN);
		b47s->cc_write(b47s, BCMA_CC_FLASHADDR, erase->addr);
		/* Newer flashes have "sub-sectors" which can be erased
		 * independently with a new command: ST_SSE. The ST_SE command
		 * erases 64KB just as before.
		 */
		if (b47s->blocksize < (64 * 1024))
			bcm47xxsflash_cmd(b47s, OPCODE_ST_SSE);
		else
			bcm47xxsflash_cmd(b47s, OPCODE_ST_SE);
		break;
	case BCM47XXSFLASH_TYPE_ATMEL:
		b47s->cc_write(b47s, BCMA_CC_FLASHADDR, erase->addr << 1);
		bcm47xxsflash_cmd(b47s, OPCODE_AT_PAGE_ERASE);
		break;
	}

	return bcm47xxsflash_poll(b47s, HZ);
}