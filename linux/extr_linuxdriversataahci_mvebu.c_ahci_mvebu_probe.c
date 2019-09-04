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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mbus_dram_target_info {int dummy; } ;
struct ahci_host_priv {int /*<<< orphan*/  stop_engine; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct ahci_host_priv*) ; 
 int PTR_ERR (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_mvebu_mbus_config (struct ahci_host_priv*,struct mbus_dram_target_info const*) ; 
 int /*<<< orphan*/  ahci_mvebu_port_info ; 
 int /*<<< orphan*/  ahci_mvebu_regret_option (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_mvebu_stop_engine ; 
 int /*<<< orphan*/  ahci_platform_disable_resources (struct ahci_host_priv*) ; 
 int ahci_platform_enable_resources (struct ahci_host_priv*) ; 
 struct ahci_host_priv* ahci_platform_get_resources (struct platform_device*,int /*<<< orphan*/ ) ; 
 int ahci_platform_init_host (struct platform_device*,struct ahci_host_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahci_platform_sht ; 
 struct mbus_dram_target_info* mv_mbus_dram_info () ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ahci_mvebu_probe(struct platform_device *pdev)
{
	struct ahci_host_priv *hpriv;
	const struct mbus_dram_target_info *dram;
	int rc;

	hpriv = ahci_platform_get_resources(pdev, 0);
	if (IS_ERR(hpriv))
		return PTR_ERR(hpriv);

	rc = ahci_platform_enable_resources(hpriv);
	if (rc)
		return rc;

	hpriv->stop_engine = ahci_mvebu_stop_engine;

	if (of_device_is_compatible(pdev->dev.of_node,
				    "marvell,armada-380-ahci")) {
		dram = mv_mbus_dram_info();
		if (!dram)
			return -ENODEV;

		ahci_mvebu_mbus_config(hpriv, dram);
		ahci_mvebu_regret_option(hpriv);
	}

	rc = ahci_platform_init_host(pdev, hpriv, &ahci_mvebu_port_info,
				     &ahci_platform_sht);
	if (rc)
		goto disable_resources;

	return 0;

disable_resources:
	ahci_platform_disable_resources(hpriv);
	return rc;
}