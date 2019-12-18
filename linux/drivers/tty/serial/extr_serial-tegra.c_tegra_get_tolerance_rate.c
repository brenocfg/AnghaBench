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
struct tegra_uart_port {int n_adjustable_baud_rates; TYPE_1__* baud_tolerance; } ;
struct TYPE_2__ {unsigned int lower_range_baud; unsigned int upper_range_baud; long tolerance; } ;

/* Variables and functions */

__attribute__((used)) static long tegra_get_tolerance_rate(struct tegra_uart_port *tup,
				     unsigned int baud, long rate)
{
	int i;

	for (i = 0; i < tup->n_adjustable_baud_rates; ++i) {
		if (baud >= tup->baud_tolerance[i].lower_range_baud &&
		    baud <= tup->baud_tolerance[i].upper_range_baud)
			return (rate + (rate *
				tup->baud_tolerance[i].tolerance) / 10000);
	}

	return rate;
}