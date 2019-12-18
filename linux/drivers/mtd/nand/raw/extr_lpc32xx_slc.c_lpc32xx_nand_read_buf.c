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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  u_char ;
struct nand_chip {int dummy; } ;
struct lpc32xx_nand_host {int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLC_DATA (int /*<<< orphan*/ ) ; 
 struct lpc32xx_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpc32xx_nand_read_buf(struct nand_chip *chip, u_char *buf, int len)
{
	struct lpc32xx_nand_host *host = nand_get_controller_data(chip);

	/* Direct device read with no ECC */
	while (len-- > 0)
		*buf++ = (uint8_t)readl(SLC_DATA(host->io_base));
}