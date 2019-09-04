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
 int /*<<< orphan*/  MV88E6XXX_G2_INT_SRC ; 
 int mv88e6xxx_g2_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mv88e6xxx_g2_int_source(struct mv88e6xxx_chip *chip, u16 *src)
{
	/* Read (and clear most of) the Interrupt Source bits */
	return mv88e6xxx_g2_read(chip, MV88E6XXX_G2_INT_SRC, src);
}