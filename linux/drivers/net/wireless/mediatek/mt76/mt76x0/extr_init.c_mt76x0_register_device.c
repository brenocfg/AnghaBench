#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sband; } ;
struct TYPE_7__ {scalar_t__ has_2ghz; scalar_t__ has_5ghz; } ;
struct TYPE_5__ {int /*<<< orphan*/  sband; } ;
struct TYPE_8__ {TYPE_2__ sband_2g; TYPE_3__ cap; TYPE_1__ sband_5g; } ;
struct mt76x02_dev {TYPE_4__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int mt76_register_device (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_config_mac_addr_list (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_init_debugfs (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_init_device (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_rates ; 
 int /*<<< orphan*/  mt76x0_init_txpower (struct mt76x02_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x0_vht_cap_mask (int /*<<< orphan*/ *) ; 

int mt76x0_register_device(struct mt76x02_dev *dev)
{
	int ret;

	mt76x02_init_device(dev);
	mt76x02_config_mac_addr_list(dev);

	ret = mt76_register_device(&dev->mt76, true, mt76x02_rates,
				   ARRAY_SIZE(mt76x02_rates));
	if (ret)
		return ret;

	if (dev->mt76.cap.has_5ghz) {
		/* overwrite unsupported features */
		mt76x0_vht_cap_mask(&dev->mt76.sband_5g.sband);
		mt76x0_init_txpower(dev, &dev->mt76.sband_5g.sband);
	}

	if (dev->mt76.cap.has_2ghz)
		mt76x0_init_txpower(dev, &dev->mt76.sband_2g.sband);

	mt76x02_init_debugfs(dev);

	return 0;
}