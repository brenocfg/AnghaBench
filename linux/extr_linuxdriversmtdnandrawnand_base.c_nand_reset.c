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
struct nand_data_interface {int dummy; } ;
struct nand_chip {struct nand_data_interface data_interface; int /*<<< orphan*/  onfi_timing_mode_default; int /*<<< orphan*/  (* select_chip ) (struct mtd_info*,int) ;} ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int nand_reset_data_interface (struct nand_chip*,int) ; 
 int nand_reset_op (struct nand_chip*) ; 
 int nand_setup_data_interface (struct nand_chip*,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int) ; 

int nand_reset(struct nand_chip *chip, int chipnr)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct nand_data_interface saved_data_intf = chip->data_interface;
	int ret;

	ret = nand_reset_data_interface(chip, chipnr);
	if (ret)
		return ret;

	/*
	 * The CS line has to be released before we can apply the new NAND
	 * interface settings, hence this weird ->select_chip() dance.
	 */
	chip->select_chip(mtd, chipnr);
	ret = nand_reset_op(chip);
	chip->select_chip(mtd, -1);
	if (ret)
		return ret;

	/*
	 * A nand_reset_data_interface() put both the NAND chip and the NAND
	 * controller in timings mode 0. If the default mode for this chip is
	 * also 0, no need to proceed to the change again. Plus, at probe time,
	 * nand_setup_data_interface() uses ->set/get_features() which would
	 * fail anyway as the parameter page is not available yet.
	 */
	if (!chip->onfi_timing_mode_default)
		return 0;

	chip->data_interface = saved_data_intf;
	ret = nand_setup_data_interface(chip, chipnr);
	if (ret)
		return ret;

	return 0;
}