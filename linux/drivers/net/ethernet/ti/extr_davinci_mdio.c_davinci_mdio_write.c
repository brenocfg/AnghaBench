#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct mii_bus {struct davinci_mdio_data* priv; } ;
struct davinci_mdio_data {int /*<<< orphan*/  dev; TYPE_2__* regs; } ;
struct TYPE_4__ {TYPE_1__* user; } ;
struct TYPE_3__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int PHY_ID_MASK ; 
 int PHY_REG_MASK ; 
 int USERACCESS_DATA ; 
 int USERACCESS_GO ; 
 int USERACCESS_WRITE ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int wait_for_user_access (struct davinci_mdio_data*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int davinci_mdio_write(struct mii_bus *bus, int phy_id,
			      int phy_reg, u16 phy_data)
{
	struct davinci_mdio_data *data = bus->priv;
	u32 reg;
	int ret;

	if (phy_reg & ~PHY_REG_MASK || phy_id & ~PHY_ID_MASK)
		return -EINVAL;

	ret = pm_runtime_get_sync(data->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(data->dev);
		return ret;
	}

	reg = (USERACCESS_GO | USERACCESS_WRITE | (phy_reg << 21) |
		   (phy_id << 16) | (phy_data & USERACCESS_DATA));

	while (1) {
		ret = wait_for_user_access(data);
		if (ret == -EAGAIN)
			continue;
		if (ret < 0)
			break;

		writel(reg, &data->regs->user[0].access);

		ret = wait_for_user_access(data);
		if (ret == -EAGAIN)
			continue;
		break;
	}

	pm_runtime_mark_last_busy(data->dev);
	pm_runtime_put_autosuspend(data->dev);

	return ret;
}