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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ S3C2410_NFSTAT ; 
 int S3C2410_NFSTAT_BUSY ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int readb (scalar_t__) ; 
 struct s3c2410_nand_info* s3c2410_nand_mtd_toinfo (struct mtd_info*) ; 

__attribute__((used)) static int s3c2410_nand_devready(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	return readb(info->regs + S3C2410_NFSTAT) & S3C2410_NFSTAT_BUSY;
}