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
 int mv88e6xxx_g2_smi_phy_write_addr_c45 (struct mv88e6xxx_chip*,int,int,int,int) ; 
 int mv88e6xxx_g2_smi_phy_write_data_c45 (struct mv88e6xxx_chip*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6xxx_g2_smi_phy_write_c45(struct mv88e6xxx_chip *chip,
					  bool external, int port, int reg,
					  u16 data)
{
	int dev = (reg >> 16) & 0x1f;
	int addr = reg & 0xffff;
	int err;

	err = mv88e6xxx_g2_smi_phy_write_addr_c45(chip, external, port, dev,
						  addr);
	if (err)
		return err;

	return mv88e6xxx_g2_smi_phy_write_data_c45(chip, external, port, dev,
						   data);
}