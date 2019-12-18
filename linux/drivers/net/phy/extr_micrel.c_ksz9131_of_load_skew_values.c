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
typedef  size_t u16 ;
struct phy_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int KSZ9131_OFFSET ; 
 int KSZ9131_SKEW_4BIT_MAX ; 
 int KSZ9131_SKEW_5BIT_MAX ; 
 int KSZ9131_STEP ; 
 int /*<<< orphan*/  of_property_read_s32 (struct device_node*,char*,int*) ; 
 size_t phy_read_mmd (struct phy_device*,int,size_t) ; 
 int phy_write_mmd (struct phy_device*,int,size_t,size_t) ; 

__attribute__((used)) static int ksz9131_of_load_skew_values(struct phy_device *phydev,
				       struct device_node *of_node,
				       u16 reg, size_t field_sz,
				       char *field[], u8 numfields)
{
	int val[4] = {-(1 + KSZ9131_OFFSET), -(2 + KSZ9131_OFFSET),
		      -(3 + KSZ9131_OFFSET), -(4 + KSZ9131_OFFSET)};
	int skewval, skewmax = 0;
	int matches = 0;
	u16 maxval;
	u16 newval;
	u16 mask;
	int i;

	/* psec properties in dts should mean x pico seconds */
	if (field_sz == 5)
		skewmax = KSZ9131_SKEW_5BIT_MAX;
	else
		skewmax = KSZ9131_SKEW_4BIT_MAX;

	for (i = 0; i < numfields; i++)
		if (!of_property_read_s32(of_node, field[i], &skewval)) {
			if (skewval < -KSZ9131_OFFSET)
				skewval = -KSZ9131_OFFSET;
			else if (skewval > skewmax)
				skewval = skewmax;

			val[i] = skewval + KSZ9131_OFFSET;
			matches++;
		}

	if (!matches)
		return 0;

	if (matches < numfields)
		newval = phy_read_mmd(phydev, 2, reg);
	else
		newval = 0;

	maxval = (field_sz == 4) ? 0xf : 0x1f;
	for (i = 0; i < numfields; i++)
		if (val[i] != -(i + 1 + KSZ9131_OFFSET)) {
			mask = 0xffff;
			mask ^= maxval << (field_sz * i);
			newval = (newval & mask) |
				(((val[i] / KSZ9131_STEP) & maxval)
					<< (field_sz * i));
		}

	return phy_write_mmd(phydev, 2, reg, newval);
}