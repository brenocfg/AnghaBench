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
struct TYPE_2__ {int /*<<< orphan*/  lpi_map; scalar_t__ lpi_base; int /*<<< orphan*/  nr_lpis; } ;
struct its_device {TYPE_1__ event_map; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 int ENOSPC ; 
 int bitmap_find_free_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_count_order (int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int its_alloc_device_irq(struct its_device *dev, int nvecs, irq_hw_number_t *hwirq)
{
	int idx;

	idx = bitmap_find_free_region(dev->event_map.lpi_map,
				      dev->event_map.nr_lpis,
				      get_count_order(nvecs));
	if (idx < 0)
		return -ENOSPC;

	*hwirq = dev->event_map.lpi_base + idx;
	set_bit(idx, dev->event_map.lpi_map);

	return 0;
}