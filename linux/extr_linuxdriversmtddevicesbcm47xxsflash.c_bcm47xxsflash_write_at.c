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
typedef  int /*<<< orphan*/  u_char ;
typedef  int u32 ;
struct mtd_info {struct bcm47xxsflash* priv; } ;
struct bcm47xxsflash {int blocksize; int /*<<< orphan*/  (* cc_write ) (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_FLASHADDR ; 
 int /*<<< orphan*/  BCMA_CC_FLASHDATA ; 
 int HZ ; 
 int /*<<< orphan*/  OPCODE_AT_BUF1_LOAD ; 
 int /*<<< orphan*/  OPCODE_AT_BUF1_PROGRAM ; 
 int /*<<< orphan*/  OPCODE_AT_BUF1_WRITE ; 
 int /*<<< orphan*/  bcm47xxsflash_cmd (struct bcm47xxsflash*,int /*<<< orphan*/ ) ; 
 int bcm47xxsflash_poll (struct bcm47xxsflash*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  stub1 (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm47xxsflash_write_at(struct mtd_info *mtd, u32 offset, size_t len,
				  const u_char *buf)
{
	struct bcm47xxsflash *b47s = mtd->priv;
	u32 mask = b47s->blocksize - 1;
	u32 page = (offset & ~mask) << 1;
	u32 byte = offset & mask;
	int written = 0;

	/* If we don't overwrite whole page, read it to the buffer first */
	if (byte || (len < b47s->blocksize)) {
		int err;

		b47s->cc_write(b47s, BCMA_CC_FLASHADDR, page);
		bcm47xxsflash_cmd(b47s, OPCODE_AT_BUF1_LOAD);
		/* 250 us for AT45DB321B */
		err = bcm47xxsflash_poll(b47s, HZ / 1000);
		if (err) {
			pr_err("Timeout reading page 0x%X info buffer\n", page);
			return err;
		}
	}

	/* Change buffer content with our data */
	while (len > 0) {
		/* Page boundary, another function call is needed */
		if (byte == b47s->blocksize)
			break;

		b47s->cc_write(b47s, BCMA_CC_FLASHADDR, byte++);
		b47s->cc_write(b47s, BCMA_CC_FLASHDATA, *buf++);
		bcm47xxsflash_cmd(b47s, OPCODE_AT_BUF1_WRITE);
		len--;
		written++;
	}

	/* Program page with the buffer content */
	b47s->cc_write(b47s, BCMA_CC_FLASHADDR, page);
	bcm47xxsflash_cmd(b47s, OPCODE_AT_BUF1_PROGRAM);

	return written;
}