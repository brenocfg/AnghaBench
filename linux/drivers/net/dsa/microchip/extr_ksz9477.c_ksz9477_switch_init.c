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
typedef  int /*<<< orphan*/  u64 ;
struct ksz_port {int dummy; } ;
struct ksz_device {scalar_t__ chip_id; int port_cnt; int port_mask; int mib_cnt; int mib_port_cnt; TYPE_3__* ports; int /*<<< orphan*/  dev; int /*<<< orphan*/  reg_mib_cnt; int /*<<< orphan*/  phy_errata_9477; int /*<<< orphan*/  cpu_ports; int /*<<< orphan*/  num_statics; int /*<<< orphan*/  num_alus; int /*<<< orphan*/  num_vlans; int /*<<< orphan*/  name; TYPE_1__* ds; } ;
struct ksz_chip_data {scalar_t__ chip_id; int port_cnt; int /*<<< orphan*/  phy_errata_9477; int /*<<< orphan*/  cpu_ports; int /*<<< orphan*/  num_statics; int /*<<< orphan*/  num_alus; int /*<<< orphan*/  num_vlans; int /*<<< orphan*/  dev_name; } ;
struct TYPE_5__ {void* counters; int /*<<< orphan*/  cnt_mutex; } ;
struct TYPE_6__ {TYPE_2__ mib; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ksz_chip_data*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SWITCH_COUNTER_NUM ; 
 int TOTAL_SWITCH_COUNTER_NUM ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ksz_chip_data* ksz9477_switch_chips ; 
 int /*<<< orphan*/  ksz9477_switch_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ksz9477_switch_init(struct ksz_device *dev)
{
	int i;

	dev->ds->ops = &ksz9477_switch_ops;

	for (i = 0; i < ARRAY_SIZE(ksz9477_switch_chips); i++) {
		const struct ksz_chip_data *chip = &ksz9477_switch_chips[i];

		if (dev->chip_id == chip->chip_id) {
			dev->name = chip->dev_name;
			dev->num_vlans = chip->num_vlans;
			dev->num_alus = chip->num_alus;
			dev->num_statics = chip->num_statics;
			dev->port_cnt = chip->port_cnt;
			dev->cpu_ports = chip->cpu_ports;
			dev->phy_errata_9477 = chip->phy_errata_9477;

			break;
		}
	}

	/* no switch found */
	if (!dev->port_cnt)
		return -ENODEV;

	dev->port_mask = (1 << dev->port_cnt) - 1;

	dev->reg_mib_cnt = SWITCH_COUNTER_NUM;
	dev->mib_cnt = TOTAL_SWITCH_COUNTER_NUM;

	i = dev->mib_port_cnt;
	dev->ports = devm_kzalloc(dev->dev, sizeof(struct ksz_port) * i,
				  GFP_KERNEL);
	if (!dev->ports)
		return -ENOMEM;
	for (i = 0; i < dev->mib_port_cnt; i++) {
		mutex_init(&dev->ports[i].mib.cnt_mutex);
		dev->ports[i].mib.counters =
			devm_kzalloc(dev->dev,
				     sizeof(u64) *
				     (TOTAL_SWITCH_COUNTER_NUM + 1),
				     GFP_KERNEL);
		if (!dev->ports[i].mib.counters)
			return -ENOMEM;
	}

	return 0;
}