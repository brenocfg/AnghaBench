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
struct nand_chip {int (* setup_data_interface ) (struct mtd_info*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  data_interface; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_SDR_IFACE ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  onfi_fill_data_interface (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (struct mtd_info*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nand_reset_data_interface(struct nand_chip *chip, int chipnr)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int ret;

	if (!chip->setup_data_interface)
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
	ret = chip->setup_data_interface(mtd, chipnr, &chip->data_interface);
	if (ret)
		pr_err("Failed to configure data interface to SDR timing mode 0\n");

	return ret;
}