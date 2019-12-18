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
struct lpc32xx_nand_host {int /*<<< orphan*/  dummy_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpc32xx_read_page (struct nand_chip*,int /*<<< orphan*/ ,int,int) ; 
 struct lpc32xx_nand_host* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static int lpc32xx_read_oob(struct nand_chip *chip, int page)
{
	struct lpc32xx_nand_host *host = nand_get_controller_data(chip);

	/* Read whole page - necessary with MLC controller! */
	lpc32xx_read_page(chip, host->dummy_buf, 1, page);

	return 0;
}