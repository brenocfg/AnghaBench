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
struct nand_chip {int dummy; } ;
struct davinci_nand_info {scalar_t__ is_readmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_4BIT_ECC1_OFFSET ; 
 int /*<<< orphan*/  davinci_nand_readl (struct davinci_nand_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_davinci_readecc_4bit (struct davinci_nand_info*,int*) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 struct davinci_nand_info* to_davinci_nand (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nand_davinci_calculate_4bit(struct nand_chip *chip,
				       const u_char *dat, u_char *ecc_code)
{
	struct davinci_nand_info *info = to_davinci_nand(nand_to_mtd(chip));
	u32 raw_ecc[4], *p;
	unsigned i;

	/* After a read, terminate ECC calculation by a dummy read
	 * of some 4-bit ECC register.  ECC covers everything that
	 * was read; correct() just uses the hardware state, so
	 * ecc_code is not needed.
	 */
	if (info->is_readmode) {
		davinci_nand_readl(info, NAND_4BIT_ECC1_OFFSET);
		return 0;
	}

	/* Pack eight raw 10-bit ecc values into ten bytes, making
	 * two passes which each convert four values (in upper and
	 * lower halves of two 32-bit words) into five bytes.  The
	 * ROM boot loader uses this same packing scheme.
	 */
	nand_davinci_readecc_4bit(info, raw_ecc);
	for (i = 0, p = raw_ecc; i < 2; i++, p += 2) {
		*ecc_code++ =   p[0]        & 0xff;
		*ecc_code++ = ((p[0] >>  8) & 0x03) | ((p[0] >> 14) & 0xfc);
		*ecc_code++ = ((p[0] >> 22) & 0x0f) | ((p[1] <<  4) & 0xf0);
		*ecc_code++ = ((p[1] >>  4) & 0x3f) | ((p[1] >> 10) & 0xc0);
		*ecc_code++ =  (p[1] >> 18) & 0xff;
	}

	return 0;
}