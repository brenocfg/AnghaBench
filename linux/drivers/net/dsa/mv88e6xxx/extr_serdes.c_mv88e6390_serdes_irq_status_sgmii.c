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
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  MV88E6390_SGMII_INT_STATUS ; 
 int mv88e6390_serdes_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mv88e6390_serdes_irq_status_sgmii(struct mv88e6xxx_chip *chip,
					     u8 lane, u16 *status)
{
	int err;

	err = mv88e6390_serdes_read(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_SGMII_INT_STATUS, status);

	return err;
}