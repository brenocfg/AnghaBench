#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct nand_chip {int options; } ;
struct atmel_nand {TYPE_2__* activecs; } ;
struct TYPE_3__ {int /*<<< orphan*/  virt; } ;
struct TYPE_4__ {TYPE_1__ io; } ;

/* Variables and functions */
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  iowrite16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 
 struct atmel_nand* to_atmel_nand (struct nand_chip*) ; 

__attribute__((used)) static void atmel_nand_write_byte(struct nand_chip *chip, u8 byte)
{
	struct atmel_nand *nand = to_atmel_nand(chip);

	if (chip->options & NAND_BUSWIDTH_16)
		iowrite16(byte | (byte << 8), nand->activecs->io.virt);
	else
		iowrite8(byte, nand->activecs->io.virt);
}