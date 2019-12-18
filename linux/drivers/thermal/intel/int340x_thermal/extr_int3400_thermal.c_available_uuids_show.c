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
struct int3400_thermal_priv {int uuid_bitmap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int INT3400_THERMAL_MAXIMUM_UUID ; 
 int PAGE_SIZE ; 
 struct int3400_thermal_priv* dev_get_drvdata (struct device*) ; 
 char** int3400_thermal_uuids ; 
 scalar_t__ snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static ssize_t available_uuids_show(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct int3400_thermal_priv *priv = dev_get_drvdata(dev);
	int i;
	int length = 0;

	for (i = 0; i < INT3400_THERMAL_MAXIMUM_UUID; i++) {
		if (priv->uuid_bitmap & (1 << i))
			if (PAGE_SIZE - length > 0)
				length += snprintf(&buf[length],
						   PAGE_SIZE - length,
						   "%s\n",
						   int3400_thermal_uuids[i]);
	}

	return length;
}