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
struct nand_chip {int dummy; } ;
struct davinci_nand_info {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NANDFSR_OFFSET ; 
 int davinci_nand_readl (struct davinci_nand_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 struct davinci_nand_info* to_davinci_nand (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nand_davinci_dev_ready(struct nand_chip *chip)
{
	struct davinci_nand_info *info = to_davinci_nand(nand_to_mtd(chip));

	return davinci_nand_readl(info, NANDFSR_OFFSET) & BIT(0);
}