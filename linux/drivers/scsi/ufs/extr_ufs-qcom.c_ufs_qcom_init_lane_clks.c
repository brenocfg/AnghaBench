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
struct ufs_qcom_host {int /*<<< orphan*/  tx_l1_sync_clk; int /*<<< orphan*/  rx_l1_sync_clk; TYPE_1__* hba; int /*<<< orphan*/  tx_l0_sync_clk; int /*<<< orphan*/  rx_l0_sync_clk; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int lanes_per_direction; struct device* dev; } ;

/* Variables and functions */
 scalar_t__ has_acpi_companion (struct device*) ; 
 int ufs_qcom_host_clk_get (struct device*,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ufs_qcom_init_lane_clks(struct ufs_qcom_host *host)
{
	int err = 0;
	struct device *dev = host->hba->dev;

	if (has_acpi_companion(dev))
		return 0;

	err = ufs_qcom_host_clk_get(dev, "rx_lane0_sync_clk",
					&host->rx_l0_sync_clk, false);
	if (err)
		goto out;

	err = ufs_qcom_host_clk_get(dev, "tx_lane0_sync_clk",
					&host->tx_l0_sync_clk, false);
	if (err)
		goto out;

	/* In case of single lane per direction, don't read lane1 clocks */
	if (host->hba->lanes_per_direction > 1) {
		err = ufs_qcom_host_clk_get(dev, "rx_lane1_sync_clk",
			&host->rx_l1_sync_clk, false);
		if (err)
			goto out;

		err = ufs_qcom_host_clk_get(dev, "tx_lane1_sync_clk",
			&host->tx_l1_sync_clk, true);
	}
out:
	return err;
}