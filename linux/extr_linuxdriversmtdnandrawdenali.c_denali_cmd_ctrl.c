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
typedef  int uint32_t ;
struct mtd_info {int dummy; } ;
struct denali_nand_info {int /*<<< orphan*/  (* host_write ) (struct denali_nand_info*,int,int) ;} ;

/* Variables and functions */
 int DENALI_BANK (struct denali_nand_info*) ; 
 int DENALI_MAP11_ADDR ; 
 int DENALI_MAP11_CMD ; 
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 unsigned int NAND_CTRL_CHANGE ; 
 int /*<<< orphan*/  denali_reset_irq (struct denali_nand_info*) ; 
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 
 int /*<<< orphan*/  stub1 (struct denali_nand_info*,int,int) ; 

__attribute__((used)) static void denali_cmd_ctrl(struct mtd_info *mtd, int dat, unsigned int ctrl)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);
	uint32_t type;

	if (ctrl & NAND_CLE)
		type = DENALI_MAP11_CMD;
	else if (ctrl & NAND_ALE)
		type = DENALI_MAP11_ADDR;
	else
		return;

	/*
	 * Some commands are followed by chip->dev_ready or chip->waitfunc.
	 * irq_status must be cleared here to catch the R/B# interrupt later.
	 */
	if (ctrl & NAND_CTRL_CHANGE)
		denali_reset_irq(denali);

	denali->host_write(denali, DENALI_BANK(denali) | type, dat);
}