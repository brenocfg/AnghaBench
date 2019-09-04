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
struct denali_nand_info {int /*<<< orphan*/  nand; } ;

/* Variables and functions */
 int /*<<< orphan*/  denali_disable_irq (struct denali_nand_info*) ; 
 int /*<<< orphan*/  nand_release (struct mtd_info*) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 

void denali_remove(struct denali_nand_info *denali)
{
	struct mtd_info *mtd = nand_to_mtd(&denali->nand);

	nand_release(mtd);
	denali_disable_irq(denali);
}