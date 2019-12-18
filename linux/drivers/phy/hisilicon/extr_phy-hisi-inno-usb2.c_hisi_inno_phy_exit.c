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
struct phy {int dummy; } ;
struct hisi_inno_phy_priv {int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  por_rst; } ;
struct hisi_inno_phy_port {int /*<<< orphan*/  utmi_rst; struct hisi_inno_phy_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct hisi_inno_phy_port* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hisi_inno_phy_exit(struct phy *phy)
{
	struct hisi_inno_phy_port *port = phy_get_drvdata(phy);
	struct hisi_inno_phy_priv *priv = port->priv;

	reset_control_assert(port->utmi_rst);
	reset_control_assert(priv->por_rst);
	clk_disable_unprepare(priv->ref_clk);

	return 0;
}