#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct powercap_zone_constraint {TYPE_2__* ops; } ;
struct powercap_zone {int const_id_cnt; struct powercap_zone_constraint* constraints; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {char* (* get_name ) (struct powercap_zone*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODATA ; 
 size_t POWERCAP_CONSTRAINT_NAME_LEN ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* stub1 (struct powercap_zone*,int) ; 
 struct powercap_zone* to_powercap_zone (struct device*) ; 

__attribute__((used)) static ssize_t show_constraint_name(struct device *dev,
				struct device_attribute *dev_attr,
				char *buf)
{
	const char *name;
	struct powercap_zone *power_zone = to_powercap_zone(dev);
	int id;
	ssize_t len = -ENODATA;
	struct powercap_zone_constraint *pconst;

	if (!sscanf(dev_attr->attr.name, "constraint_%d_", &id))
		return -EINVAL;
	if (id >= power_zone->const_id_cnt)
		return -EINVAL;
	pconst = &power_zone->constraints[id];

	if (pconst && pconst->ops && pconst->ops->get_name) {
		name = pconst->ops->get_name(power_zone, id);
		if (name) {
			snprintf(buf, POWERCAP_CONSTRAINT_NAME_LEN,
								"%s\n", name);
			buf[POWERCAP_CONSTRAINT_NAME_LEN] = '\0';
			len = strlen(buf);
		}
	}

	return len;
}