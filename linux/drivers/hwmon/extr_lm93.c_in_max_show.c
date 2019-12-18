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
struct lm93_data {TYPE_1__* block7; int /*<<< orphan*/ * vccp_limits; int /*<<< orphan*/ * vid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int index; } ;
struct TYPE_3__ {int /*<<< orphan*/  max; } ;

/* Variables and functions */
 long LM93_IN_FROM_REG (int,int /*<<< orphan*/ ) ; 
 long LM93_IN_MAX_FROM_REG (int /*<<< orphan*/ ,long) ; 
 long LM93_VID_FROM_REG (int /*<<< orphan*/ ) ; 
 struct lm93_data* lm93_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 TYPE_2__* to_sensor_dev_attr (struct device_attribute*) ; 
 scalar_t__* vccp_limit_type ; 

__attribute__((used)) static ssize_t in_max_show(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	int nr = (to_sensor_dev_attr(attr))->index;
	struct lm93_data *data = lm93_update_device(dev);
	int vccp = nr - 6;
	long rc, vid;

	if ((nr == 6 || nr == 7) && vccp_limit_type[vccp]) {
		vid = LM93_VID_FROM_REG(data->vid[vccp]);
		rc = LM93_IN_MAX_FROM_REG(data->vccp_limits[vccp], vid);
	} else {
		rc = LM93_IN_FROM_REG(nr, data->block7[nr].max);
	}
	return sprintf(buf, "%ld\n", rc);
}