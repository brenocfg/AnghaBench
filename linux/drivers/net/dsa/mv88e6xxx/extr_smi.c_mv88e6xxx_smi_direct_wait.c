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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ETIMEDOUT ; 
 int mv88e6xxx_smi_direct_read (struct mv88e6xxx_chip*,int,int,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mv88e6xxx_smi_direct_wait(struct mv88e6xxx_chip *chip,
				     int dev, int reg, int bit, int val)
{
	u16 data;
	int err;
	int i;

	for (i = 0; i < 16; i++) {
		err = mv88e6xxx_smi_direct_read(chip, dev, reg, &data);
		if (err)
			return err;

		if (!!(data & BIT(bit)) == !!val)
			return 0;

		usleep_range(1000, 2000);
	}

	return -ETIMEDOUT;
}