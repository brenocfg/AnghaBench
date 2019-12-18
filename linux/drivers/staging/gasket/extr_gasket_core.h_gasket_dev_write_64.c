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
typedef  int /*<<< orphan*/  u64 ;
struct gasket_dev {TYPE_1__* bar_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * virt_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  writeq_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void gasket_dev_write_64(struct gasket_dev *dev, u64 value,
				       int bar, ulong location)
{
	writeq_relaxed(value, &dev->bar_data[bar].virt_base[location]);
}