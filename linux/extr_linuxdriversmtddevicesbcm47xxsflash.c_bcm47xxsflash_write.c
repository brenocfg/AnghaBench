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
struct mtd_info {struct bcm47xxsflash* priv; } ;
struct bcm47xxsflash {int type; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
#define  BCM47XXSFLASH_TYPE_ATMEL 129 
#define  BCM47XXSFLASH_TYPE_ST 128 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int bcm47xxsflash_write_at (struct mtd_info*,scalar_t__,size_t,int /*<<< orphan*/  const*) ; 
 int bcm47xxsflash_write_st (struct mtd_info*,scalar_t__,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 

__attribute__((used)) static int bcm47xxsflash_write(struct mtd_info *mtd, loff_t to, size_t len,
			       size_t *retlen, const u_char *buf)
{
	struct bcm47xxsflash *b47s = mtd->priv;
	int written;

	/* Writing functions can return without writing all passed data, for
	 * example when the hardware is too old or when we git page boundary.
	 */
	while (len > 0) {
		switch (b47s->type) {
		case BCM47XXSFLASH_TYPE_ST:
			written = bcm47xxsflash_write_st(mtd, to, len, buf);
			break;
		case BCM47XXSFLASH_TYPE_ATMEL:
			written = bcm47xxsflash_write_at(mtd, to, len, buf);
			break;
		default:
			BUG_ON(1);
		}
		if (written < 0) {
			pr_err("Error writing at offset 0x%llX\n", to);
			return written;
		}
		to += (loff_t)written;
		len -= written;
		*retlen += written;
		buf += written;
	}

	return 0;
}