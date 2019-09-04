#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtd_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  IO_ADDR_W; } ;
struct gpiomtd {TYPE_1__ nand_chip; scalar_t__ ale; scalar_t__ cle; scalar_t__ nce; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_CTRL_CHANGE ; 
 unsigned int NAND_NCE ; 
 int /*<<< orphan*/  gpio_nand_dosync (struct gpiomtd*) ; 
 struct gpiomtd* gpio_nand_getpriv (struct mtd_info*) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_nand_cmd_ctrl(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct gpiomtd *gpiomtd = gpio_nand_getpriv(mtd);

	gpio_nand_dosync(gpiomtd);

	if (ctrl & NAND_CTRL_CHANGE) {
		if (gpiomtd->nce)
			gpiod_set_value(gpiomtd->nce, !(ctrl & NAND_NCE));
		gpiod_set_value(gpiomtd->cle, !!(ctrl & NAND_CLE));
		gpiod_set_value(gpiomtd->ale, !!(ctrl & NAND_ALE));
		gpio_nand_dosync(gpiomtd);
	}
	if (cmd == NAND_CMD_NONE)
		return;

	writeb(cmd, gpiomtd->nand_chip.IO_ADDR_W);
	gpio_nand_dosync(gpiomtd);
}