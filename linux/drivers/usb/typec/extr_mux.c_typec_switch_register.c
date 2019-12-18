#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct typec_switch_desc {int /*<<< orphan*/  drvdata; int /*<<< orphan*/  fwnode; scalar_t__ set; } ;
struct TYPE_5__ {int /*<<< orphan*/  driver_data; int /*<<< orphan*/ * type; int /*<<< orphan*/ * class; int /*<<< orphan*/  fwnode; struct device* parent; } ;
struct typec_switch {TYPE_1__ dev; scalar_t__ set; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct typec_switch* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 struct typec_switch* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  typec_mux_class ; 
 int /*<<< orphan*/  typec_switch_dev_type ; 

struct typec_switch *
typec_switch_register(struct device *parent,
		      const struct typec_switch_desc *desc)
{
	struct typec_switch *sw;
	int ret;

	if (!desc || !desc->set)
		return ERR_PTR(-EINVAL);

	sw = kzalloc(sizeof(*sw), GFP_KERNEL);
	if (!sw)
		return ERR_PTR(-ENOMEM);

	sw->set = desc->set;

	device_initialize(&sw->dev);
	sw->dev.parent = parent;
	sw->dev.fwnode = desc->fwnode;
	sw->dev.class = &typec_mux_class;
	sw->dev.type = &typec_switch_dev_type;
	sw->dev.driver_data = desc->drvdata;
	dev_set_name(&sw->dev, "%s-switch", dev_name(parent));

	ret = device_add(&sw->dev);
	if (ret) {
		dev_err(parent, "failed to register switch (%d)\n", ret);
		put_device(&sw->dev);
		return ERR_PTR(ret);
	}

	return sw;
}