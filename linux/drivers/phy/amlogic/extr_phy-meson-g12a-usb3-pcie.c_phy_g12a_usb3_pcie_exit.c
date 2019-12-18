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
struct phy_g12a_usb3_pcie_priv {int /*<<< orphan*/  reset; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 struct phy_g12a_usb3_pcie_priv* phy_get_drvdata (struct phy*) ; 
 int reset_control_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_g12a_usb3_pcie_exit(struct phy *phy)
{
	struct phy_g12a_usb3_pcie_priv *priv = phy_get_drvdata(phy);

	return reset_control_reset(priv->reset);
}