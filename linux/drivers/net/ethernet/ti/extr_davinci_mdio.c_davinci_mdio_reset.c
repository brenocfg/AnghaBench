#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mii_bus {struct davinci_mdio_data* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_freq; } ;
struct davinci_mdio_data {int access_time; int /*<<< orphan*/  dev; TYPE_3__* bus; TYPE_2__* regs; scalar_t__ skip_scan; TYPE_1__ pdata; } ;
struct TYPE_6__ {int phy_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  alive; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int PHY_MAX_ADDR ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int davinci_mdio_reset(struct mii_bus *bus)
{
	struct davinci_mdio_data *data = bus->priv;
	u32 phy_mask, ver;
	int ret;

	ret = pm_runtime_get_sync(data->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(data->dev);
		return ret;
	}

	/* wait for scan logic to settle */
	msleep(PHY_MAX_ADDR * data->access_time);

	/* dump hardware version info */
	ver = readl(&data->regs->version);
	dev_info(data->dev,
		 "davinci mdio revision %d.%d, bus freq %ld\n",
		 (ver >> 8) & 0xff, ver & 0xff,
		 data->pdata.bus_freq);

	if (data->skip_scan)
		goto done;

	/* get phy mask from the alive register */
	phy_mask = readl(&data->regs->alive);
	if (phy_mask) {
		/* restrict mdio bus to live phys only */
		dev_info(data->dev, "detected phy mask %x\n", ~phy_mask);
		phy_mask = ~phy_mask;
	} else {
		/* desperately scan all phys */
		dev_warn(data->dev, "no live phy, scanning all\n");
		phy_mask = 0;
	}
	data->bus->phy_mask = phy_mask;

done:
	pm_runtime_mark_last_busy(data->dev);
	pm_runtime_put_autosuspend(data->dev);

	return 0;
}