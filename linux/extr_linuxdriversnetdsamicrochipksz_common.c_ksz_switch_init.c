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
struct ksz_device {scalar_t__ chip_id; int /*<<< orphan*/  port_cnt; int /*<<< orphan*/  cpu_ports; int /*<<< orphan*/  num_statics; int /*<<< orphan*/  num_alus; int /*<<< orphan*/  num_vlans; int /*<<< orphan*/  name; TYPE_1__* ds; } ;
struct ksz_chip_data {scalar_t__ chip_id; int /*<<< orphan*/  cpu_ports; int /*<<< orphan*/  port_cnt; int /*<<< orphan*/  num_statics; int /*<<< orphan*/  num_alus; int /*<<< orphan*/  num_vlans; int /*<<< orphan*/  dev_name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ksz_chip_data*) ; 
 int ENODEV ; 
 struct ksz_chip_data* ksz_switch_chips ; 
 int /*<<< orphan*/  ksz_switch_ops ; 

__attribute__((used)) static int ksz_switch_init(struct ksz_device *dev)
{
	int i;

	dev->ds->ops = &ksz_switch_ops;

	for (i = 0; i < ARRAY_SIZE(ksz_switch_chips); i++) {
		const struct ksz_chip_data *chip = &ksz_switch_chips[i];

		if (dev->chip_id == chip->chip_id) {
			dev->name = chip->dev_name;
			dev->num_vlans = chip->num_vlans;
			dev->num_alus = chip->num_alus;
			dev->num_statics = chip->num_statics;
			dev->port_cnt = chip->port_cnt;
			dev->cpu_ports = chip->cpu_ports;

			break;
		}
	}

	/* no switch found */
	if (!dev->port_cnt)
		return -ENODEV;

	return 0;
}