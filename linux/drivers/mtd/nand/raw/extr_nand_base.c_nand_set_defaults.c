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
struct TYPE_2__ {int /*<<< orphan*/  dummy_controller; } ;
struct nand_chip {int buf_align; int /*<<< orphan*/ * controller; TYPE_1__ legacy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_controller_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_legacy_set_defaults (struct nand_chip*) ; 

__attribute__((used)) static void nand_set_defaults(struct nand_chip *chip)
{
	/* If no controller is provided, use the dummy, legacy one. */
	if (!chip->controller) {
		chip->controller = &chip->legacy.dummy_controller;
		nand_controller_init(chip->controller);
	}

	nand_legacy_set_defaults(chip);

	if (!chip->buf_align)
		chip->buf_align = 1;
}