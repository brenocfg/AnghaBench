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
typedef  int u32 ;
struct lan9303 {int /*<<< orphan*/  indirect_mutex; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAN9303_PMI_ACCESS ; 
 int LAN9303_PMI_ACCESS_MIIRINDA (int) ; 
 int LAN9303_PMI_ACCESS_PHY_ADDR (int) ; 
 int /*<<< orphan*/  LAN9303_PMI_DATA ; 
 int lan9303_indirect_phy_wait_for_completion (struct lan9303*) ; 
 int lan9303_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan9303_indirect_phy_read(struct lan9303 *chip, int addr, int regnum)
{
	int ret;
	u32 val;

	val = LAN9303_PMI_ACCESS_PHY_ADDR(addr);
	val |= LAN9303_PMI_ACCESS_MIIRINDA(regnum);

	mutex_lock(&chip->indirect_mutex);

	ret = lan9303_indirect_phy_wait_for_completion(chip);
	if (ret)
		goto on_error;

	/* start the MII read cycle */
	ret = regmap_write(chip->regmap, LAN9303_PMI_ACCESS, val);
	if (ret)
		goto on_error;

	ret = lan9303_indirect_phy_wait_for_completion(chip);
	if (ret)
		goto on_error;

	/* read the result of this operation */
	ret = lan9303_read(chip->regmap, LAN9303_PMI_DATA, &val);
	if (ret)
		goto on_error;

	mutex_unlock(&chip->indirect_mutex);

	return val & 0xffff;

on_error:
	mutex_unlock(&chip->indirect_mutex);
	return ret;
}