#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  attr; } ;
struct pmbus_samples_reg {int page; TYPE_1__ dev_attr; struct pmbus_samples_attr* attr; } ;
struct pmbus_samples_attr {int /*<<< orphan*/  name; } ;
struct pmbus_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pmbus_samples_reg* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pmbus_add_attribute (struct pmbus_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmbus_dev_attr_init (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmbus_set_samples ; 
 int /*<<< orphan*/  pmbus_show_samples ; 

__attribute__((used)) static int pmbus_add_samples_attr(struct pmbus_data *data, int page,
				  struct pmbus_samples_attr *attr)
{
	struct pmbus_samples_reg *reg;

	reg = devm_kzalloc(data->dev, sizeof(*reg), GFP_KERNEL);
	if (!reg)
		return -ENOMEM;

	reg->attr = attr;
	reg->page = page;

	pmbus_dev_attr_init(&reg->dev_attr, attr->name, 0644,
			    pmbus_show_samples, pmbus_set_samples);

	return pmbus_add_attribute(data, &reg->dev_attr.attr);
}