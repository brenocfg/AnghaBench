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
 int MV88E6085_G1_CTL2_P10RM ; 
 int MV88E6085_G1_CTL2_RM_ENABLE ; 
 int mv88e6xxx_g1_ctl2_mask (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 

int mv88e6085_g1_rmu_disable(struct mv88e6xxx_chip *chip)
{
	return mv88e6xxx_g1_ctl2_mask(chip, MV88E6085_G1_CTL2_P10RM |
				      MV88E6085_G1_CTL2_RM_ENABLE, 0);
}