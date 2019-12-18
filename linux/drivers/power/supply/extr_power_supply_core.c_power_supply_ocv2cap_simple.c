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
struct power_supply_battery_ocv_table {int ocv; int capacity; } ;

/* Variables and functions */

int power_supply_ocv2cap_simple(struct power_supply_battery_ocv_table *table,
				int table_len, int ocv)
{
	int i, cap, tmp;

	for (i = 0; i < table_len; i++)
		if (ocv > table[i].ocv)
			break;

	if (i > 0 && i < table_len) {
		tmp = (table[i - 1].capacity - table[i].capacity) *
			(ocv - table[i].ocv);
		tmp /= table[i - 1].ocv - table[i].ocv;
		cap = tmp + table[i].capacity;
	} else if (i == 0) {
		cap = table[0].capacity;
	} else {
		cap = table[table_len - 1].capacity;
	}

	return cap;
}