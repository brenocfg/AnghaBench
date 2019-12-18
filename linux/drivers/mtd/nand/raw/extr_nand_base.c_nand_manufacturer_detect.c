#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nand_memory_organization {int /*<<< orphan*/  bits_per_cell; } ;
struct TYPE_7__ {TYPE_4__* desc; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct nand_chip {TYPE_3__ manufacturer; TYPE_1__ id; int /*<<< orphan*/  base; } ;
struct TYPE_8__ {TYPE_2__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* detect ) (struct nand_chip*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nand_decode_ext_id (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_get_bits_per_cell (int /*<<< orphan*/ ) ; 
 struct nand_memory_organization* nanddev_get_memorg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*) ; 

__attribute__((used)) static void nand_manufacturer_detect(struct nand_chip *chip)
{
	/*
	 * Try manufacturer detection if available and use
	 * nand_decode_ext_id() otherwise.
	 */
	if (chip->manufacturer.desc && chip->manufacturer.desc->ops &&
	    chip->manufacturer.desc->ops->detect) {
		struct nand_memory_organization *memorg;

		memorg = nanddev_get_memorg(&chip->base);

		/* The 3rd id byte holds MLC / multichip data */
		memorg->bits_per_cell = nand_get_bits_per_cell(chip->id.data[2]);
		chip->manufacturer.desc->ops->detect(chip);
	} else {
		nand_decode_ext_id(chip);
	}
}