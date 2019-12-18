#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nand_chip {int /*<<< orphan*/  data_interface; TYPE_2__* controller; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* setup_data_interface ) (struct nand_chip*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_SDR_IFACE ; 
 int /*<<< orphan*/  nand_has_setup_data_iface (struct nand_chip*) ; 
 int /*<<< orphan*/  onfi_fill_data_interface (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (struct nand_chip*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nand_reset_data_interface(struct nand_chip *chip, int chipnr)
{
	int ret;

	if (!nand_has_setup_data_iface(chip))
		return 0;

	/*
	 * The ONFI specification says:
	 * "
	 * To transition from NV-DDR or NV-DDR2 to the SDR data
	 * interface, the host shall use the Reset (FFh) command
	 * using SDR timing mode 0. A device in any timing mode is
	 * required to recognize Reset (FFh) command issued in SDR
	 * timing mode 0.
	 * "
	 *
	 * Configure the data interface in SDR mode and set the
	 * timings to timing mode 0.
	 */

	onfi_fill_data_interface(chip, NAND_SDR_IFACE, 0);
	ret = chip->controller->ops->setup_data_interface(chip, chipnr,
							&chip->data_interface);
	if (ret)
		pr_err("Failed to configure data interface to SDR timing mode 0\n");

	return ret;
}