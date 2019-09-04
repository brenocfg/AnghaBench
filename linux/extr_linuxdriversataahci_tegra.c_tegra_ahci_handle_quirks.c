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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_ahci_priv {scalar_t__ sata_aux_regs; TYPE_1__* soc; } ;
struct ahci_host_priv {struct tegra_ahci_priv* plat_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  supports_devslp; } ;

/* Variables and functions */
 scalar_t__ SATA_AUX_MISC_CNTL_1_0 ; 
 int /*<<< orphan*/  SATA_AUX_MISC_CNTL_1_0_SDS_SUPPORT ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tegra_ahci_handle_quirks(struct ahci_host_priv *hpriv)
{
	struct tegra_ahci_priv *tegra = hpriv->plat_data;
	u32 val;

	if (tegra->sata_aux_regs && !tegra->soc->supports_devslp) {
		val = readl(tegra->sata_aux_regs + SATA_AUX_MISC_CNTL_1_0);
		val &= ~SATA_AUX_MISC_CNTL_1_0_SDS_SUPPORT;
		writel(val, tegra->sata_aux_regs + SATA_AUX_MISC_CNTL_1_0);
	}
}