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
struct cphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODULE_DEV_ADDR ; 
 int ael_i2c_rd (struct cphy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int phy_modtype_lr ; 
 int phy_modtype_lrm ; 
 int phy_modtype_sr ; 
 int phy_modtype_twinax ; 
 int phy_modtype_twinax_long ; 
 int phy_modtype_unknown ; 

__attribute__((used)) static int ael2xxx_get_module_type(struct cphy *phy, int delay_ms)
{
	int v;

	if (delay_ms)
		msleep(delay_ms);

	/* see SFF-8472 for below */
	v = ael_i2c_rd(phy, MODULE_DEV_ADDR, 3);
	if (v < 0)
		return v;

	if (v == 0x10)
		return phy_modtype_sr;
	if (v == 0x20)
		return phy_modtype_lr;
	if (v == 0x40)
		return phy_modtype_lrm;

	v = ael_i2c_rd(phy, MODULE_DEV_ADDR, 6);
	if (v < 0)
		return v;
	if (v != 4)
		goto unknown;

	v = ael_i2c_rd(phy, MODULE_DEV_ADDR, 10);
	if (v < 0)
		return v;

	if (v & 0x80) {
		v = ael_i2c_rd(phy, MODULE_DEV_ADDR, 0x12);
		if (v < 0)
			return v;
		return v > 10 ? phy_modtype_twinax_long : phy_modtype_twinax;
	}
unknown:
	return phy_modtype_unknown;
}