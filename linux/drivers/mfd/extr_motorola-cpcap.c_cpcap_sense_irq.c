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
struct regmap {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int CPCAP_REGISTER_BITS ; 
 int CPCAP_REGISTER_SIZE ; 
 int CPCAP_REG_INTS1 ; 
 int CPCAP_REG_INTS4 ; 
 int EINVAL ; 
 int regmap_read (struct regmap*,int,int*) ; 

__attribute__((used)) static int cpcap_sense_irq(struct regmap *regmap, int irq)
{
	int regnum = irq / CPCAP_REGISTER_BITS;
	int mask = BIT(irq % CPCAP_REGISTER_BITS);
	int reg = CPCAP_REG_INTS1 + (regnum * CPCAP_REGISTER_SIZE);
	int err, val;

	if (reg < CPCAP_REG_INTS1 || reg > CPCAP_REG_INTS4)
		return -EINVAL;

	err = regmap_read(regmap, reg, &val);
	if (err)
		return err;

	return !!(val & mask);
}