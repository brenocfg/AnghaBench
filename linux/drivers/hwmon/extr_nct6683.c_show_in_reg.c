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
struct sensor_device_attribute_2 {int index; int nr; } ;
struct nct6683_data {int /*<<< orphan*/ * in_index; int /*<<< orphan*/ ** in; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  in_from_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nct6683_data* nct6683_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
show_in_reg(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	struct nct6683_data *data = nct6683_update_device(dev);
	int index = sattr->index;
	int nr = sattr->nr;

	return sprintf(buf, "%ld\n",
		       in_from_reg(data->in[index][nr], data->in_index[index]));
}