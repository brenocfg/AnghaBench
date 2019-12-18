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
struct qcom_nand_controller {int /*<<< orphan*/  dev; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 

__attribute__((used)) static void qcom_nandc_select_chip(struct nand_chip *chip, int chipnr)
{
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	if (chipnr <= 0)
		return;

	dev_warn(nandc->dev, "invalid chip select\n");
}