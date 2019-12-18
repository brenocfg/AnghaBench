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
struct tango_chip {scalar_t__ base; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 scalar_t__ PBUS_ADDR ; 
 scalar_t__ PBUS_CMD ; 
 struct tango_chip* to_tango_chip (struct nand_chip*) ; 
 int /*<<< orphan*/  writeb_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void tango_cmd_ctrl(struct nand_chip *chip, int dat, unsigned int ctrl)
{
	struct tango_chip *tchip = to_tango_chip(chip);

	if (ctrl & NAND_CLE)
		writeb_relaxed(dat, tchip->base + PBUS_CMD);

	if (ctrl & NAND_ALE)
		writeb_relaxed(dat, tchip->base + PBUS_ADDR);
}