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
struct mtd_info {int dummy; } ;
struct denali_nand_info {int dummy; } ;

/* Variables and functions */
 int INTR__INT_ACT ; 
 int denali_check_irq (struct denali_nand_info*) ; 
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 

__attribute__((used)) static int denali_dev_ready(struct mtd_info *mtd)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);

	return !!(denali_check_irq(denali) & INTR__INT_ACT);
}