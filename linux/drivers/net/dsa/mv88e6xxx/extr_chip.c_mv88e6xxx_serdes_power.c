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
 int /*<<< orphan*/  mv88e6xxx_serdes_get_lane (struct mv88e6xxx_chip*,int) ; 
 int mv88e6xxx_serdes_irq_free (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_serdes_irq_request (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_serdes_power_down (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_serdes_power_up (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6xxx_serdes_power(struct mv88e6xxx_chip *chip, int port,
				  bool on)
{
	u8 lane;
	int err;

	lane = mv88e6xxx_serdes_get_lane(chip, port);
	if (!lane)
		return 0;

	if (on) {
		err = mv88e6xxx_serdes_power_up(chip, port, lane);
		if (err)
			return err;

		err = mv88e6xxx_serdes_irq_request(chip, port, lane);
	} else {
		err = mv88e6xxx_serdes_irq_free(chip, port, lane);
		if (err)
			return err;

		err = mv88e6xxx_serdes_power_down(chip, port, lane);
	}

	return err;
}