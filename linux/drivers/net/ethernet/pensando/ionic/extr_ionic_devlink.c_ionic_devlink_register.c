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
struct ionic {TYPE_1__* master_lif; int /*<<< orphan*/  dl_port; int /*<<< orphan*/  dev; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_PORT_FLAVOUR_PHYSICAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devlink_port_attrs_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devlink_port_register (struct devlink*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_port_type_eth_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devlink_register (struct devlink*,int /*<<< orphan*/ ) ; 
 struct devlink* priv_to_devlink (struct ionic*) ; 

int ionic_devlink_register(struct ionic *ionic)
{
	struct devlink *dl = priv_to_devlink(ionic);
	int err;

	err = devlink_register(dl, ionic->dev);
	if (err) {
		dev_warn(ionic->dev, "devlink_register failed: %d\n", err);
		return err;
	}

	devlink_port_attrs_set(&ionic->dl_port, DEVLINK_PORT_FLAVOUR_PHYSICAL,
			       0, false, 0, NULL, 0);
	err = devlink_port_register(dl, &ionic->dl_port, 0);
	if (err)
		dev_err(ionic->dev, "devlink_port_register failed: %d\n", err);
	else
		devlink_port_type_eth_set(&ionic->dl_port,
					  ionic->master_lif->netdev);

	return err;
}