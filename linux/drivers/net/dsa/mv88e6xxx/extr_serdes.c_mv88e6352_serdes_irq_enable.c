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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6352_SERDES_INT_ENABLE ; 
 int /*<<< orphan*/  MV88E6352_SERDES_INT_LINK_CHANGE ; 
 int mv88e6352_serdes_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mv88e6352_serdes_irq_enable(struct mv88e6xxx_chip *chip, int port, u8 lane,
				bool enable)
{
	u16 val = 0;

	if (enable)
		val |= MV88E6352_SERDES_INT_LINK_CHANGE;

	return mv88e6352_serdes_write(chip, MV88E6352_SERDES_INT_ENABLE, val);
}