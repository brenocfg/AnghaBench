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
struct realtek_smi {int cpu_port; int /*<<< orphan*/  map; int /*<<< orphan*/  dev; } ;
struct phy_device {int dummy; } ;
struct dsa_switch {struct realtek_smi* priv; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  RTL8366RB_MAC_FORCE_CTRL_REG ; 
 int /*<<< orphan*/  RTL8366RB_PAACR2 ; 
 int RTL8366RB_PAACR_CPU_PORT ; 
 int /*<<< orphan*/  RTL8366RB_PECR ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl8366rb_adjust_link(struct dsa_switch *ds, int port,
				  struct phy_device *phydev)
{
	struct realtek_smi *smi = ds->priv;
	int ret;

	if (port != smi->cpu_port)
		return;

	dev_info(smi->dev, "adjust link on CPU port (%d)\n", port);

	/* Force the fixed CPU port into 1Gbit mode, no autonegotiation */
	ret = regmap_update_bits(smi->map, RTL8366RB_MAC_FORCE_CTRL_REG,
				 BIT(port), BIT(port));
	if (ret)
		return;

	ret = regmap_update_bits(smi->map, RTL8366RB_PAACR2,
				 0xFF00U,
				 RTL8366RB_PAACR_CPU_PORT << 8);
	if (ret)
		return;

	/* Enable the CPU port */
	ret = regmap_update_bits(smi->map, RTL8366RB_PECR, BIT(port),
				 0);
	if (ret)
		return;
}