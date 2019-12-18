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
struct s3c2410_nand_info {scalar_t__ regs; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ S3C2440_NFDATA ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  readsl (scalar_t__,int /*<<< orphan*/ *,int) ; 
 struct s3c2410_nand_info* s3c2410_nand_mtd_toinfo (struct mtd_info*) ; 

__attribute__((used)) static void s3c2440_nand_read_buf(struct nand_chip *this, u_char *buf, int len)
{
	struct mtd_info *mtd = nand_to_mtd(this);
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	readsl(info->regs + S3C2440_NFDATA, buf, len >> 2);

	/* cleanup if we've got less than a word to do */
	if (len & 3) {
		buf += len & ~3;

		for (; len & 3; len--)
			*buf++ = readb(info->regs + S3C2440_NFDATA);
	}
}