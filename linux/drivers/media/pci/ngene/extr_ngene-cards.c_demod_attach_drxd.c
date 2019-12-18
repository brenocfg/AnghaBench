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
struct ngene_channel {size_t number; int /*<<< orphan*/  fe; TYPE_2__* dev; int /*<<< orphan*/  i2c_adapter; } ;
struct drxd_config {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct drxd_config** fe_config; } ;
struct TYPE_5__ {TYPE_1__* pci_dev; TYPE_3__* card_info; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  drxd_attach ; 
 int /*<<< orphan*/  dvb_attach (int /*<<< orphan*/ ,struct drxd_config*,struct ngene_channel*,int /*<<< orphan*/ *,struct device*) ; 

__attribute__((used)) static int demod_attach_drxd(struct ngene_channel *chan)
{
	struct device *pdev = &chan->dev->pci_dev->dev;
	struct drxd_config *feconf;

	feconf = chan->dev->card_info->fe_config[chan->number];

	chan->fe = dvb_attach(drxd_attach, feconf, chan,
			&chan->i2c_adapter, &chan->dev->pci_dev->dev);
	if (!chan->fe) {
		dev_err(pdev, "No DRXD found!\n");
		return -ENODEV;
	}
	return 0;
}