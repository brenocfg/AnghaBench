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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int mv88e6xxx_g2_switch_mac_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 

int mv88e6xxx_g2_set_switch_mac(struct mv88e6xxx_chip *chip, u8 *addr)
{
	int i, err;

	for (i = 0; i < 6; i++) {
		err = mv88e6xxx_g2_switch_mac_write(chip, i, addr[i]);
		if (err)
			break;
	}

	return err;
}