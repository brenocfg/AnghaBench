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
struct pmbus_sensor_attr {int func; scalar_t__ paged; } ;
struct pmbus_driver_info {int pages; int* func; } ;

/* Variables and functions */

__attribute__((used)) static bool pmbus_sensor_is_paged(const struct pmbus_driver_info *info,
				  const struct pmbus_sensor_attr *attr)
{
	int p;

	if (attr->paged)
		return true;

	/*
	 * Some attributes may be present on more than one page despite
	 * not being marked with the paged attribute. If that is the case,
	 * then treat the sensor as being paged and add the page suffix to the
	 * attribute name.
	 * We don't just add the paged attribute to all such attributes, in
	 * order to maintain the un-suffixed labels in the case where the
	 * attribute is only on page 0.
	 */
	for (p = 1; p < info->pages; p++) {
		if (info->func[p] & attr->func)
			return true;
	}
	return false;
}