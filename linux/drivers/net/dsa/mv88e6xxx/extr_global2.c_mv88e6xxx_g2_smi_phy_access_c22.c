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
 int mv88e6xxx_g2_smi_phy_access (struct mv88e6xxx_chip*,int,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mv88e6xxx_g2_smi_phy_access_c22(struct mv88e6xxx_chip *chip,
					   bool external, u16 op, int dev,
					   int reg)
{
	return mv88e6xxx_g2_smi_phy_access(chip, external, false, op, dev, reg);
}