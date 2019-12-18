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
struct int3400_thermal_priv {int uuid_bitmap; int current_uuid_index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct int3400_thermal_priv* dev_get_drvdata (struct device*) ; 
 char** int3400_thermal_uuids ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t current_uuid_show(struct device *dev,
				 struct device_attribute *devattr, char *buf)
{
	struct int3400_thermal_priv *priv = dev_get_drvdata(dev);

	if (priv->uuid_bitmap & (1 << priv->current_uuid_index))
		return sprintf(buf, "%s\n",
			       int3400_thermal_uuids[priv->current_uuid_index]);
	else
		return sprintf(buf, "INVALID\n");
}