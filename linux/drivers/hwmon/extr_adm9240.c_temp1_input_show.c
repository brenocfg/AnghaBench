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
struct adm9240_data {int temp; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct adm9240_data* adm9240_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t temp1_input_show(struct device *dev,
				struct device_attribute *dummy, char *buf)
{
	struct adm9240_data *data = adm9240_update_device(dev);
	return sprintf(buf, "%d\n", data->temp / 128 * 500); /* 9-bit value */
}