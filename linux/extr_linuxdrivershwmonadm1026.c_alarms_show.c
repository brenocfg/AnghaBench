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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm1026_data {int /*<<< orphan*/  alarms; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct adm1026_data* adm1026_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t alarms_show(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	struct adm1026_data *data = adm1026_update_device(dev);
	return sprintf(buf, "%ld\n", data->alarms);
}