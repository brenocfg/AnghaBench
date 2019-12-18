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
typedef  int u16 ;
struct mv88e6xxx_chip {int /*<<< orphan*/  sw_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_SMI_CMD ; 
 int MV88E6XXX_SMI_CMD_BUSY ; 
 int MV88E6XXX_SMI_CMD_MODE_22 ; 
 int MV88E6XXX_SMI_CMD_OP_22_WRITE ; 
 int /*<<< orphan*/  MV88E6XXX_SMI_DATA ; 
 int mv88e6xxx_smi_direct_wait (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_smi_direct_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e6xxx_smi_indirect_write(struct mv88e6xxx_chip *chip,
					int dev, int reg, u16 data)
{
	int err;

	err = mv88e6xxx_smi_direct_wait(chip, chip->sw_addr,
					MV88E6XXX_SMI_CMD, 15, 0);
	if (err)
		return err;

	err = mv88e6xxx_smi_direct_write(chip, chip->sw_addr,
					 MV88E6XXX_SMI_DATA, data);
	if (err)
		return err;

	err = mv88e6xxx_smi_direct_write(chip, chip->sw_addr,
					 MV88E6XXX_SMI_CMD,
					 MV88E6XXX_SMI_CMD_BUSY |
					 MV88E6XXX_SMI_CMD_MODE_22 |
					 MV88E6XXX_SMI_CMD_OP_22_WRITE |
					 (dev << 5) | reg);
	if (err)
		return err;

	return mv88e6xxx_smi_direct_wait(chip, chip->sw_addr,
					 MV88E6XXX_SMI_CMD, 15, 0);
}