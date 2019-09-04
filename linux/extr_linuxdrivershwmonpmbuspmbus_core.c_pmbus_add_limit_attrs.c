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
struct pmbus_sensor_attr {int nlimit; int sfunc; scalar_t__ sbase; scalar_t__ compare; scalar_t__ update; int /*<<< orphan*/  class; struct pmbus_limit_attr* limit; } ;
struct pmbus_sensor {int dummy; } ;
struct pmbus_limit_attr {scalar_t__ sbit; scalar_t__ low; int /*<<< orphan*/  alarm; scalar_t__ update; int /*<<< orphan*/  reg; int /*<<< orphan*/  attr; } ;
struct pmbus_driver_info {int* func; } ;
struct pmbus_data {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int pmbus_add_boolean (struct pmbus_data*,char const*,int /*<<< orphan*/ ,int,struct pmbus_sensor*,struct pmbus_sensor*,scalar_t__,scalar_t__) ; 
 struct pmbus_sensor* pmbus_add_sensor (struct pmbus_data*,char const*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ pmbus_check_word_register (struct i2c_client*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmbus_add_limit_attrs(struct i2c_client *client,
				 struct pmbus_data *data,
				 const struct pmbus_driver_info *info,
				 const char *name, int index, int page,
				 struct pmbus_sensor *base,
				 const struct pmbus_sensor_attr *attr)
{
	const struct pmbus_limit_attr *l = attr->limit;
	int nlimit = attr->nlimit;
	int have_alarm = 0;
	int i, ret;
	struct pmbus_sensor *curr;

	for (i = 0; i < nlimit; i++) {
		if (pmbus_check_word_register(client, page, l->reg)) {
			curr = pmbus_add_sensor(data, name, l->attr, index,
						page, l->reg, attr->class,
						attr->update || l->update,
						false, true);
			if (!curr)
				return -ENOMEM;
			if (l->sbit && (info->func[page] & attr->sfunc)) {
				ret = pmbus_add_boolean(data, name,
					l->alarm, index,
					attr->compare ?  l->low ? curr : base
						      : NULL,
					attr->compare ? l->low ? base : curr
						      : NULL,
					attr->sbase + page, l->sbit);
				if (ret)
					return ret;
				have_alarm = 1;
			}
		}
		l++;
	}
	return have_alarm;
}