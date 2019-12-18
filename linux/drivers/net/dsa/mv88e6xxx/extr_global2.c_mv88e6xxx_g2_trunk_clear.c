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
typedef  scalar_t__ u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int mv88e6xxx_g2_trunk_mapping_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_g2_trunk_mask_write (struct mv88e6xxx_chip*,int,int,scalar_t__ const) ; 
 int /*<<< orphan*/  mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 

int mv88e6xxx_g2_trunk_clear(struct mv88e6xxx_chip *chip)
{
	const u16 port_mask = BIT(mv88e6xxx_num_ports(chip)) - 1;
	int i, err;

	/* Clear all eight possible Trunk Mask vectors */
	for (i = 0; i < 8; ++i) {
		err = mv88e6xxx_g2_trunk_mask_write(chip, i, false, port_mask);
		if (err)
			return err;
	}

	/* Clear all sixteen possible Trunk ID routing vectors */
	for (i = 0; i < 16; ++i) {
		err = mv88e6xxx_g2_trunk_mapping_write(chip, i, 0);
		if (err)
			return err;
	}

	return 0;
}