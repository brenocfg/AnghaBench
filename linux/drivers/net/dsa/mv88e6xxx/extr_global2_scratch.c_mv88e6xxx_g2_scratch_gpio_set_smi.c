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
typedef  int u8 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int MV88E6352_G2_SCRATCH_CONFIG_DATA1 ; 
 int MV88E6352_G2_SCRATCH_CONFIG_DATA1_NO_CPU ; 
 int MV88E6352_G2_SCRATCH_CONFIG_DATA2 ; 
 int MV88E6352_G2_SCRATCH_CONFIG_DATA2_P0_MODE_MASK ; 
 int MV88E6352_G2_SCRATCH_MISC_CFG ; 
 int MV88E6352_G2_SCRATCH_MISC_CFG_NORMALSMI ; 
 int mv88e6xxx_g2_scratch_read (struct mv88e6xxx_chip*,int,int*) ; 
 int mv88e6xxx_g2_scratch_write (struct mv88e6xxx_chip*,int,int) ; 

int mv88e6xxx_g2_scratch_gpio_set_smi(struct mv88e6xxx_chip *chip,
				      bool external)
{
	int misc_cfg = MV88E6352_G2_SCRATCH_MISC_CFG;
	int config_data1 = MV88E6352_G2_SCRATCH_CONFIG_DATA1;
	int config_data2 = MV88E6352_G2_SCRATCH_CONFIG_DATA2;
	bool no_cpu;
	u8 p0_mode;
	int err;
	u8 val;

	err = mv88e6xxx_g2_scratch_read(chip, config_data2, &val);
	if (err)
		return err;

	p0_mode = val & MV88E6352_G2_SCRATCH_CONFIG_DATA2_P0_MODE_MASK;

	if (p0_mode == 0x01 || p0_mode == 0x02)
		return -EBUSY;

	err = mv88e6xxx_g2_scratch_read(chip, config_data1, &val);
	if (err)
		return err;

	no_cpu = !!(val & MV88E6352_G2_SCRATCH_CONFIG_DATA1_NO_CPU);

	err = mv88e6xxx_g2_scratch_read(chip, misc_cfg, &val);
	if (err)
		return err;

	/* NO_CPU being 0 inverts the meaning of the bit */
	if (!no_cpu)
		external = !external;

	if (external)
		val |= MV88E6352_G2_SCRATCH_MISC_CFG_NORMALSMI;
	else
		val &= ~MV88E6352_G2_SCRATCH_MISC_CFG_NORMALSMI;

	return mv88e6xxx_g2_scratch_write(chip, misc_cfg, val);
}