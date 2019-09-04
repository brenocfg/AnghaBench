#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sa1111_dev {int /*<<< orphan*/ * hwirq; } ;
struct sa1111 {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 struct sa1111* sa1111_chip_driver (struct sa1111_dev*) ; 
 int sa1111_map_irq (struct sa1111*,int /*<<< orphan*/ ) ; 

int sa1111_get_irq(struct sa1111_dev *sadev, unsigned num)
{
	struct sa1111 *sachip = sa1111_chip_driver(sadev);
	if (num >= ARRAY_SIZE(sadev->hwirq))
		return -EINVAL;
	return sa1111_map_irq(sachip, sadev->hwirq[num]);
}