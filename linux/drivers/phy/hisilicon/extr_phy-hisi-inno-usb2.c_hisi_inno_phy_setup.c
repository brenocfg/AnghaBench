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
struct hisi_inno_phy_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_CLK_ENABLE ; 
 int /*<<< orphan*/  PHY_CLK_STABLE_TIME ; 
 int /*<<< orphan*/  hisi_inno_phy_write_reg (struct hisi_inno_phy_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hisi_inno_phy_setup(struct hisi_inno_phy_priv *priv)
{
	/* The phy clk is controlled by the port0 register 0x06. */
	hisi_inno_phy_write_reg(priv, 0, 0x06, PHY_CLK_ENABLE);
	msleep(PHY_CLK_STABLE_TIME);
}