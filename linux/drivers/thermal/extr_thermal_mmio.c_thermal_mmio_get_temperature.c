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
struct thermal_mmio {int (* read_mmio ) (int /*<<< orphan*/ ) ;int mask; int factor; int /*<<< orphan*/  mmio_base; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int thermal_mmio_get_temperature(void *private, int *temp)
{
	int t;
	struct thermal_mmio *sensor =
		(struct thermal_mmio *)private;

	t = sensor->read_mmio(sensor->mmio_base) & sensor->mask;
	t *= sensor->factor;

	*temp = t;

	return 0;
}