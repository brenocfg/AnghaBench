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
struct s3c2410_nand_info {scalar_t__ regs; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 unsigned long S3C2412_NFCONT_INIT_MAIN_ECC ; 
 scalar_t__ S3C2440_NFCONT ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 unsigned long readl (scalar_t__) ; 
 struct s3c2410_nand_info* s3c2410_nand_mtd_toinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void s3c2412_nand_enable_hwecc(struct nand_chip *chip, int mode)
{
	struct s3c2410_nand_info *info;
	unsigned long ctrl;

	info = s3c2410_nand_mtd_toinfo(nand_to_mtd(chip));
	ctrl = readl(info->regs + S3C2440_NFCONT);
	writel(ctrl | S3C2412_NFCONT_INIT_MAIN_ECC,
	       info->regs + S3C2440_NFCONT);
}