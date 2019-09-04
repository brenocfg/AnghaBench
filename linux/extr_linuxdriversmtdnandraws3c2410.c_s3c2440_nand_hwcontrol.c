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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 scalar_t__ S3C2440_NFADDR ; 
 scalar_t__ S3C2440_NFCMD ; 
 struct s3c2410_nand_info* s3c2410_nand_mtd_toinfo (struct mtd_info*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void s3c2440_nand_hwcontrol(struct mtd_info *mtd, int cmd,
				   unsigned int ctrl)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
		writeb(cmd, info->regs + S3C2440_NFCMD);
	else
		writeb(cmd, info->regs + S3C2440_NFADDR);
}