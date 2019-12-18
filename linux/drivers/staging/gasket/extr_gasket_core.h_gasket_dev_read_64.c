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
typedef  size_t ulong ;
struct gasket_dev {TYPE_1__* bar_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * virt_base; } ;

/* Variables and functions */
 size_t readq_relaxed (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline ulong gasket_dev_read_64(struct gasket_dev *gasket_dev, int bar,
				       ulong location)
{
	return readq_relaxed(&gasket_dev->bar_data[bar].virt_base[location]);
}