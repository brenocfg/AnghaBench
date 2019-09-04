#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra_ahci_priv {int /*<<< orphan*/  supplies; TYPE_1__* soc; int /*<<< orphan*/  sata_clk; int /*<<< orphan*/  sata_oob_rst; int /*<<< orphan*/  sata_cold_rst; int /*<<< orphan*/  sata_rst; } ;
struct ahci_host_priv {struct tegra_ahci_priv* plat_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_POWERGATE_SATA ; 
 int ahci_platform_enable_resources (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_powergate_power_off (int /*<<< orphan*/ ) ; 
 int tegra_powergate_sequence_power_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_ahci_power_on(struct ahci_host_priv *hpriv)
{
	struct tegra_ahci_priv *tegra = hpriv->plat_data;
	int ret;

	ret = regulator_bulk_enable(tegra->soc->num_supplies,
				    tegra->supplies);
	if (ret)
		return ret;

	ret = tegra_powergate_sequence_power_up(TEGRA_POWERGATE_SATA,
						tegra->sata_clk,
						tegra->sata_rst);
	if (ret)
		goto disable_regulators;

	reset_control_assert(tegra->sata_oob_rst);
	reset_control_assert(tegra->sata_cold_rst);

	ret = ahci_platform_enable_resources(hpriv);
	if (ret)
		goto disable_power;

	reset_control_deassert(tegra->sata_cold_rst);
	reset_control_deassert(tegra->sata_oob_rst);

	return 0;

disable_power:
	clk_disable_unprepare(tegra->sata_clk);

	tegra_powergate_power_off(TEGRA_POWERGATE_SATA);

disable_regulators:
	regulator_bulk_disable(tegra->soc->num_supplies, tegra->supplies);

	return ret;
}