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
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_smi_write (struct mv88e6xxx_chip*,int,int,int /*<<< orphan*/ ) ; 

int mv88e6xxx_write(struct mv88e6xxx_chip *chip, int addr, int reg, u16 val)
{
	int err;

	assert_reg_lock(chip);

	err = mv88e6xxx_smi_write(chip, addr, reg, val);
	if (err)
		return err;

	dev_dbg(chip->dev, "-> addr: 0x%.2x reg: 0x%.2x val: 0x%.4x\n",
		addr, reg, val);

	return 0;
}