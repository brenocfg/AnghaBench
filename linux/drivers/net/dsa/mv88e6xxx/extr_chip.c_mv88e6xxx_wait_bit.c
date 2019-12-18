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
 int BIT (int) ; 
 int mv88e6xxx_wait_mask (struct mv88e6xxx_chip*,int,int,int,int) ; 

int mv88e6xxx_wait_bit(struct mv88e6xxx_chip *chip, int addr, int reg,
		       int bit, int val)
{
	return mv88e6xxx_wait_mask(chip, addr, reg, BIT(bit),
				   val ? BIT(bit) : 0x0000);
}