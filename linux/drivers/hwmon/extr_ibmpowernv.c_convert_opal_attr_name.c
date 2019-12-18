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
typedef  enum sensors { ____Placeholder_sensors } sensors ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DATA_ATTR_SUFFIX ; 
 int /*<<< orphan*/  DT_FAULT_ATTR_SUFFIX ; 
 int /*<<< orphan*/  DT_THRESHOLD_ATTR_SUFFIX ; 
 int FAN ; 
 int TEMP ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *convert_opal_attr_name(enum sensors type,
					  const char *opal_attr)
{
	const char *attr_name = NULL;

	if (!strcmp(opal_attr, DT_FAULT_ATTR_SUFFIX)) {
		attr_name = "fault";
	} else if (!strcmp(opal_attr, DT_DATA_ATTR_SUFFIX)) {
		attr_name = "input";
	} else if (!strcmp(opal_attr, DT_THRESHOLD_ATTR_SUFFIX)) {
		if (type == TEMP)
			attr_name = "max";
		else if (type == FAN)
			attr_name = "min";
	}

	return attr_name;
}