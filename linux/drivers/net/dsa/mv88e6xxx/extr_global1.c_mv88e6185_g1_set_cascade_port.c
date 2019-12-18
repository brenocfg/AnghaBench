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
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6185_G1_CTL2_CASCADE_PORT_MASK ; 
 int __bf_shf (int /*<<< orphan*/  const) ; 
 int mv88e6xxx_g1_ctl2_mask (struct mv88e6xxx_chip*,int /*<<< orphan*/  const,int) ; 

int mv88e6185_g1_set_cascade_port(struct mv88e6xxx_chip *chip, int port)
{
	const u16 mask = MV88E6185_G1_CTL2_CASCADE_PORT_MASK;

	return mv88e6xxx_g1_ctl2_mask(chip, mask, port << __bf_shf(mask));
}