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
struct smb347_charger {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  STAT_A ; 
 unsigned int STAT_A_FLOAT_VOLTAGE_MASK ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  smb347_is_ps_online (struct smb347_charger*) ; 

__attribute__((used)) static int get_const_charge_voltage(struct smb347_charger *smb)
{
	int ret, intval;
	unsigned int v;

	if (!smb347_is_ps_online(smb))
		return -ENODATA;

	ret = regmap_read(smb->regmap, STAT_A, &v);
	if (ret < 0)
		return ret;

	v &= STAT_A_FLOAT_VOLTAGE_MASK;
	if (v > 0x3d)
		v = 0x3d;

	intval = 3500000 + v * 20000;

	return intval;
}