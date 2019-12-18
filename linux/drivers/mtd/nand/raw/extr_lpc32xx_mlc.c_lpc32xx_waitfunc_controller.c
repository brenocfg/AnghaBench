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
struct mtd_info {int /*<<< orphan*/  dev; } ;
struct lpc32xx_nand_host {int /*<<< orphan*/  io_base; int /*<<< orphan*/  comp_controller; } ;

/* Variables and functions */
 int MLCISR_CONTROLLER_READY ; 
 int /*<<< orphan*/  MLC_ISR (int /*<<< orphan*/ ) ; 
 int NAND_STATUS_READY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct lpc32xx_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc32xx_waitfunc_controller(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct lpc32xx_nand_host *host = nand_get_controller_data(chip);

	if (readb(MLC_ISR(host->io_base)) & MLCISR_CONTROLLER_READY)
		goto exit;

	wait_for_completion(&host->comp_controller);

	while (!(readb(MLC_ISR(host->io_base)) &
		 MLCISR_CONTROLLER_READY)) {
		dev_dbg(&mtd->dev, "Warning: Controller not ready.\n");
		cpu_relax();
	}

exit:
	return NAND_STATUS_READY;
}