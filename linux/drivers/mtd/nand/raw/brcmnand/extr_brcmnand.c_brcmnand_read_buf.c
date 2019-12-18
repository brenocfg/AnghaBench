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
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmnand_read_byte (struct nand_chip*) ; 

__attribute__((used)) static void brcmnand_read_buf(struct nand_chip *chip, uint8_t *buf, int len)
{
	int i;

	for (i = 0; i < len; i++, buf++)
		*buf = brcmnand_read_byte(chip);
}