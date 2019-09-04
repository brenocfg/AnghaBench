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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct denali_nand_info {int dummy; } ;

/* Variables and functions */
 int INTR__INT_ACT ; 
 int NAND_STATUS_FAIL ; 
 int denali_wait_for_irq (struct denali_nand_info*,int) ; 
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 

__attribute__((used)) static int denali_waitfunc(struct mtd_info *mtd, struct nand_chip *chip)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);
	uint32_t irq_status;

	/* R/B# pin transitioned from low to high? */
	irq_status = denali_wait_for_irq(denali, INTR__INT_ACT);

	return irq_status & INTR__INT_ACT ? 0 : NAND_STATUS_FAIL;
}