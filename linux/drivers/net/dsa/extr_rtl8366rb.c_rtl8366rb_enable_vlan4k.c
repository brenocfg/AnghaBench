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
struct realtek_smi {int /*<<< orphan*/  map; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8366RB_SGCR ; 
 int /*<<< orphan*/  RTL8366RB_SGCR_EN_VLAN_4KTB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8366rb_enable_vlan4k(struct realtek_smi *smi, bool enable)
{
	dev_dbg(smi->dev, "%s VLAN 4k\n", enable ? "enable" : "disable");
	return regmap_update_bits(smi->map, RTL8366RB_SGCR,
				  RTL8366RB_SGCR_EN_VLAN_4KTB,
				  enable ? RTL8366RB_SGCR_EN_VLAN_4KTB : 0);
}