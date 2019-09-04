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
struct nand_chip {int dummy; } ;
struct TYPE_2__ {struct micron_nand* rawbuf; } ;
struct micron_nand {TYPE_1__ ecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct micron_nand*) ; 
 struct micron_nand* nand_get_manufacturer_data (struct nand_chip*) ; 

__attribute__((used)) static void micron_nand_cleanup(struct nand_chip *chip)
{
	struct micron_nand *micron = nand_get_manufacturer_data(chip);

	kfree(micron->ecc.rawbuf);
	kfree(micron);
}