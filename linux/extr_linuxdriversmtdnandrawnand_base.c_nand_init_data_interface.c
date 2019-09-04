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
struct nand_chip {int (* setup_data_interface ) (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int onfi_timing_mode_default; int /*<<< orphan*/  data_interface; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAND_DATA_IFACE_CHECK_ONLY ; 
 int /*<<< orphan*/  NAND_SDR_IFACE ; 
 int ONFI_TIMING_MODE_UNKNOWN ; 
 int fls (int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int onfi_fill_data_interface (struct nand_chip*,int /*<<< orphan*/ ,int) ; 
 int onfi_get_async_timing_mode (struct nand_chip*) ; 
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nand_init_data_interface(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int modes, mode, ret;

	if (!chip->setup_data_interface)
		return 0;

	/*
	 * First try to identify the best timings from ONFI parameters and
	 * if the NAND does not support ONFI, fallback to the default ONFI
	 * timing mode.
	 */
	modes = onfi_get_async_timing_mode(chip);
	if (modes == ONFI_TIMING_MODE_UNKNOWN) {
		if (!chip->onfi_timing_mode_default)
			return 0;

		modes = GENMASK(chip->onfi_timing_mode_default, 0);
	}


	for (mode = fls(modes) - 1; mode >= 0; mode--) {
		ret = onfi_fill_data_interface(chip, NAND_SDR_IFACE, mode);
		if (ret)
			continue;

		/*
		 * Pass NAND_DATA_IFACE_CHECK_ONLY to only check if the
		 * controller supports the requested timings.
		 */
		ret = chip->setup_data_interface(mtd,
						 NAND_DATA_IFACE_CHECK_ONLY,
						 &chip->data_interface);
		if (!ret) {
			chip->onfi_timing_mode_default = mode;
			break;
		}
	}

	return 0;
}