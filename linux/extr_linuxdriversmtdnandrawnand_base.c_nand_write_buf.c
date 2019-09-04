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
struct nand_chip {int /*<<< orphan*/  IO_ADDR_W; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite8_rep (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static void nand_write_buf(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	iowrite8_rep(chip->IO_ADDR_W, buf, len);
}