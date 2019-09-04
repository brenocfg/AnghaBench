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
struct mv88e6xxx_chip {TYPE_1__* ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_CMODE_INVALID ; 
 int mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static void mv88e6xxx_ports_cmode_init(struct mv88e6xxx_chip *chip)
{
	int i;

	for (i = 0; i < mv88e6xxx_num_ports(chip); i++)
		chip->ports[i].cmode = MV88E6XXX_PORT_STS_CMODE_INVALID;
}