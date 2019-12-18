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
struct lpc32xx_nand_host {int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 int SLCSTAT_NAND_READY ; 
 int /*<<< orphan*/  SLC_STAT (int /*<<< orphan*/ ) ; 
 struct lpc32xx_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc32xx_nand_device_ready(struct nand_chip *chip)
{
	struct lpc32xx_nand_host *host = nand_get_controller_data(chip);
	int rdy = 0;

	if ((readl(SLC_STAT(host->io_base)) & SLCSTAT_NAND_READY) != 0)
		rdy = 1;

	return rdy;
}