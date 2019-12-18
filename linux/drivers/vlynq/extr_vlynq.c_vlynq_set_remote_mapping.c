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
typedef  int /*<<< orphan*/  u32 ;
struct vlynq_mapping {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct vlynq_device {TYPE_2__* remote; int /*<<< orphan*/  enabled; } ;
struct TYPE_4__ {TYPE_1__* rx_mapping; int /*<<< orphan*/  tx_offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int vlynq_set_remote_mapping(struct vlynq_device *dev, u32 tx_offset,
			     struct vlynq_mapping *mapping)
{
	int i;

	if (!dev->enabled)
		return -ENXIO;

	writel(tx_offset, &dev->remote->tx_offset);
	for (i = 0; i < 4; i++) {
		writel(mapping[i].offset, &dev->remote->rx_mapping[i].offset);
		writel(mapping[i].size, &dev->remote->rx_mapping[i].size);
	}
	return 0;
}