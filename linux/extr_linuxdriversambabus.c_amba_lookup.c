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
struct amba_id {int mask; int id; } ;
struct amba_device {int periphid; } ;

/* Variables and functions */

__attribute__((used)) static const struct amba_id *
amba_lookup(const struct amba_id *table, struct amba_device *dev)
{
	int ret = 0;

	while (table->mask) {
		ret = (dev->periphid & table->mask) == table->id;
		if (ret)
			break;
		table++;
	}

	return ret ? table : NULL;
}