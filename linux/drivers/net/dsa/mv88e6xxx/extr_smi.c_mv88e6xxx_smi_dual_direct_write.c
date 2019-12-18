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
struct mv88e6xxx_chip {scalar_t__ sw_addr; } ;

/* Variables and functions */
 int mv88e6xxx_smi_direct_write (struct mv88e6xxx_chip*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6xxx_smi_dual_direct_write(struct mv88e6xxx_chip *chip,
					   int dev, int reg, u16 data)
{
	return mv88e6xxx_smi_direct_write(chip, chip->sw_addr + dev, reg, data);
}