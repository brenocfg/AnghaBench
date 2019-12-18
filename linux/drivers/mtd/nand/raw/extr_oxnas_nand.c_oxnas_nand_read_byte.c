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
typedef  int /*<<< orphan*/  uint8_t ;
struct oxnas_nand_ctrl {int /*<<< orphan*/  io_base; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 struct oxnas_nand_ctrl* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t oxnas_nand_read_byte(struct nand_chip *chip)
{
	struct oxnas_nand_ctrl *oxnas = nand_get_controller_data(chip);

	return readb(oxnas->io_base);
}