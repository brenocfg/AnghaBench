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
struct mtd_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int lpc32xx_nand_ecc_calculate(struct mtd_info *mtd,
				      const unsigned char *buf,
				      unsigned char *code)
{
	/*
	 * ECC is calculated automatically in hardware during syndrome read
	 * and write operations, so it doesn't need to be calculated here.
	 */
	return 0;
}