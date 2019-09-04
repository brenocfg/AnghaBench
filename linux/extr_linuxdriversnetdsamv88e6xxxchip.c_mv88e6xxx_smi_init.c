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
struct mv88e6xxx_chip {int sw_addr; struct mii_bus* bus; int /*<<< orphan*/ * smi_ops; TYPE_1__* info; } ;
struct mii_bus {int dummy; } ;
struct TYPE_2__ {scalar_t__ multi_chip; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mv88e6xxx_smi_multi_chip_ops ; 
 int /*<<< orphan*/  mv88e6xxx_smi_single_chip_ops ; 

__attribute__((used)) static int mv88e6xxx_smi_init(struct mv88e6xxx_chip *chip,
			      struct mii_bus *bus, int sw_addr)
{
	if (sw_addr == 0)
		chip->smi_ops = &mv88e6xxx_smi_single_chip_ops;
	else if (chip->info->multi_chip)
		chip->smi_ops = &mv88e6xxx_smi_multi_chip_ops;
	else
		return -EINVAL;

	chip->bus = bus;
	chip->sw_addr = sw_addr;

	return 0;
}