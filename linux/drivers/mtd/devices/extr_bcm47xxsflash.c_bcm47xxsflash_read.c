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
struct mtd_info {scalar_t__ size; struct bcm47xxsflash* priv; } ;
struct bcm47xxsflash {scalar_t__ window; int /*<<< orphan*/  (* cc_read ) (struct bcm47xxsflash*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cc_write ) (struct bcm47xxsflash*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ BCM47XXSFLASH_WINDOW_SZ ; 
 int /*<<< orphan*/  BCMA_CC_FLASHADDR ; 
 int /*<<< orphan*/  BCMA_CC_FLASHDATA ; 
 int EINVAL ; 
 int /*<<< orphan*/  OPCODE_ST_READ4B ; 
 int /*<<< orphan*/  bcm47xxsflash_cmd (struct bcm47xxsflash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  stub1 (struct bcm47xxsflash*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct bcm47xxsflash*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm47xxsflash_read(struct mtd_info *mtd, loff_t from, size_t len,
			      size_t *retlen, u_char *buf)
{
	struct bcm47xxsflash *b47s = mtd->priv;
	size_t orig_len = len;

	/* Check address range */
	if ((from + len) > mtd->size)
		return -EINVAL;

	/* Read as much as possible using fast MMIO window */
	if (from < BCM47XXSFLASH_WINDOW_SZ) {
		size_t memcpy_len;

		memcpy_len = min(len, (size_t)(BCM47XXSFLASH_WINDOW_SZ - from));
		memcpy_fromio(buf, b47s->window + from, memcpy_len);
		from += memcpy_len;
		len -= memcpy_len;
		buf += memcpy_len;
	}

	/* Use indirect access for content out of the window */
	for (; len; len--) {
		b47s->cc_write(b47s, BCMA_CC_FLASHADDR, from++);
		bcm47xxsflash_cmd(b47s, OPCODE_ST_READ4B);
		*buf++ = b47s->cc_read(b47s, BCMA_CC_FLASHDATA);
	}

	*retlen = orig_len;

	return orig_len;
}