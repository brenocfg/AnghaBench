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
struct denali_nand_info {int active_bank; } ;

/* Variables and functions */
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 

__attribute__((used)) static void denali_select_chip(struct mtd_info *mtd, int chip)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);

	denali->active_bank = chip;
}