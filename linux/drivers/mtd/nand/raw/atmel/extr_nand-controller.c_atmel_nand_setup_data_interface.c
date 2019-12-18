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
struct nand_data_interface {int dummy; } ;
struct nand_chip {int dummy; } ;
struct atmel_nand_controller {TYPE_3__* caps; } ;
struct TYPE_4__ {int /*<<< orphan*/  controller; } ;
struct atmel_nand {int numcs; TYPE_1__ base; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int (* setup_data_interface ) (struct atmel_nand*,int,struct nand_data_interface const*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int NAND_DATA_IFACE_CHECK_ONLY ; 
 int stub1 (struct atmel_nand*,int,struct nand_data_interface const*) ; 
 struct atmel_nand* to_atmel_nand (struct nand_chip*) ; 
 struct atmel_nand_controller* to_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_nand_setup_data_interface(struct nand_chip *chip, int csline,
					const struct nand_data_interface *conf)
{
	struct atmel_nand *nand = to_atmel_nand(chip);
	struct atmel_nand_controller *nc;

	nc = to_nand_controller(nand->base.controller);

	if (csline >= nand->numcs ||
	    (csline < 0 && csline != NAND_DATA_IFACE_CHECK_ONLY))
		return -EINVAL;

	return nc->caps->ops->setup_data_interface(nand, csline, conf);
}