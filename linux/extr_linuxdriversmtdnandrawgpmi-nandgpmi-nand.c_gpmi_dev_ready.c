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
struct mtd_info {int dummy; } ;
struct gpmi_nand_data {int /*<<< orphan*/  current_chip; } ;

/* Variables and functions */
 int gpmi_is_ready (struct gpmi_nand_data*,int /*<<< orphan*/ ) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct gpmi_nand_data* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static int gpmi_dev_ready(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct gpmi_nand_data *this = nand_get_controller_data(chip);

	return gpmi_is_ready(this, this->current_chip);
}