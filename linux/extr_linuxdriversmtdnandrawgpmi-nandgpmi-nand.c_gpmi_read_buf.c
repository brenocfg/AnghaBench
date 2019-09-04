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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct gpmi_nand_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpmi_read_data (struct gpmi_nand_data*,int /*<<< orphan*/ *,int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct gpmi_nand_data* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void gpmi_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct gpmi_nand_data *this = nand_get_controller_data(chip);

	dev_dbg(this->dev, "len is %d\n", len);

	gpmi_read_data(this, buf, len);
}