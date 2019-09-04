#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* desc; } ;
struct nand_chip {TYPE_3__ manufacturer; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cleanup ) (struct nand_chip*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nand_chip*) ; 

__attribute__((used)) static void nand_manufacturer_cleanup(struct nand_chip *chip)
{
	/* Release manufacturer private data */
	if (chip->manufacturer.desc && chip->manufacturer.desc->ops &&
	    chip->manufacturer.desc->ops->cleanup)
		chip->manufacturer.desc->ops->cleanup(chip);
}