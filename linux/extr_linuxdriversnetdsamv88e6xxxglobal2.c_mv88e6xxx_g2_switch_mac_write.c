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
typedef  unsigned int u8 ;
typedef  unsigned int u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_G2_SWITCH_MAC ; 
 int mv88e6xxx_g2_update (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mv88e6xxx_g2_switch_mac_write(struct mv88e6xxx_chip *chip,
					 unsigned int pointer, u8 data)
{
	u16 val = (pointer << 8) | data;

	return mv88e6xxx_g2_update(chip, MV88E6XXX_G2_SWITCH_MAC, val);
}