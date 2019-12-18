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

/* Variables and functions */
 int /*<<< orphan*/  NAND_READ_DATA ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 unsigned char xway_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char xway_read_byte(struct nand_chip *chip)
{
	return xway_readb(nand_to_mtd(chip), NAND_READ_DATA);
}