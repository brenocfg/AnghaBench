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
struct mtd_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int lpc32xx_write_oob(struct mtd_info *mtd, struct nand_chip *chip,
			      int page)
{
	/* None, write_oob conflicts with the automatic LPC MLC ECC decoder! */
	return 0;
}