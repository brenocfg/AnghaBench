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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ mv88e6352_port_has_serdes (struct mv88e6xxx_chip*,int) ; 
 int /*<<< orphan*/  mv88e6352_serdes_hw_stats ; 

int mv88e6352_serdes_get_sset_count(struct mv88e6xxx_chip *chip, int port)
{
	if (mv88e6352_port_has_serdes(chip, port))
		return ARRAY_SIZE(mv88e6352_serdes_hw_stats);

	return 0;
}