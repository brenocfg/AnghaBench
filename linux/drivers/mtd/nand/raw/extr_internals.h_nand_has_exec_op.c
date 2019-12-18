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
struct nand_chip {TYPE_2__* controller; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  exec_op; } ;

/* Variables and functions */

__attribute__((used)) static inline bool nand_has_exec_op(struct nand_chip *chip)
{
	if (!chip->controller || !chip->controller->ops ||
	    !chip->controller->ops->exec_op)
		return false;

	return true;
}