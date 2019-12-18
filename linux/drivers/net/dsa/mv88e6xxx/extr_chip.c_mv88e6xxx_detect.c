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
typedef  unsigned int u16 ;
struct mv88e6xxx_info {int /*<<< orphan*/  name; int /*<<< orphan*/  prod_num; } ;
struct mv88e6xxx_chip {struct mv88e6xxx_info const* info; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_SWITCH_ID ; 
 unsigned int MV88E6XXX_PORT_SWITCH_ID_PROD_MASK ; 
 unsigned int MV88E6XXX_PORT_SWITCH_ID_REV_MASK ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int mv88e6xxx_g2_require (struct mv88e6xxx_chip*) ; 
 struct mv88e6xxx_info* mv88e6xxx_lookup_info (unsigned int) ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6xxx_detect(struct mv88e6xxx_chip *chip)
{
	const struct mv88e6xxx_info *info;
	unsigned int prod_num, rev;
	u16 id;
	int err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_read(chip, 0, MV88E6XXX_PORT_SWITCH_ID, &id);
	mv88e6xxx_reg_unlock(chip);
	if (err)
		return err;

	prod_num = id & MV88E6XXX_PORT_SWITCH_ID_PROD_MASK;
	rev = id & MV88E6XXX_PORT_SWITCH_ID_REV_MASK;

	info = mv88e6xxx_lookup_info(prod_num);
	if (!info)
		return -ENODEV;

	/* Update the compatible info with the probed one */
	chip->info = info;

	err = mv88e6xxx_g2_require(chip);
	if (err)
		return err;

	dev_info(chip->dev, "switch 0x%x detected: %s, revision %u\n",
		 chip->info->prod_num, chip->info->name, rev);

	return 0;
}