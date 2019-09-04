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
struct lan9303 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LAN9303_VIRT_PHY_BASE ; 
 int MII_EXPANSION ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan9303_virt_phy_reg_write(struct lan9303 *chip, int regnum, u16 val)
{
	if (regnum > MII_EXPANSION)
		return -EINVAL;

	return regmap_write(chip->regmap, LAN9303_VIRT_PHY_BASE + regnum, val);
}