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
struct of_device_id {void const* data; scalar_t__* compatible; scalar_t__* type; scalar_t__* name; } ;
struct dsa_mv88e6xxx_pdata {int /*<<< orphan*/  compatible; } ;
struct device {struct dsa_mv88e6xxx_pdata* platform_data; TYPE_1__* driver; } ;
struct TYPE_2__ {struct of_device_id* of_match_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static const void *pdata_device_get_match_data(struct device *dev)
{
	const struct of_device_id *matches = dev->driver->of_match_table;
	const struct dsa_mv88e6xxx_pdata *pdata = dev->platform_data;

	for (; matches->name[0] || matches->type[0] || matches->compatible[0];
	     matches++) {
		if (!strcmp(pdata->compatible, matches->compatible))
			return matches->data;
	}
	return NULL;
}