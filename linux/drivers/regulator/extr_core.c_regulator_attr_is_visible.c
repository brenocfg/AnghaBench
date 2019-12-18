#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_23__ ;
typedef  struct TYPE_37__   TYPE_22__ ;
typedef  struct TYPE_36__   TYPE_21__ ;
typedef  struct TYPE_35__   TYPE_20__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_19__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct regulator_ops {scalar_t__ (* get_voltage ) (struct regulator_dev*) ;scalar_t__ (* get_voltage_sel ) (struct regulator_dev*) ;scalar_t__ (* list_voltage ) (struct regulator_dev*,int /*<<< orphan*/ ) ;scalar_t__ set_suspend_mode; scalar_t__ set_suspend_voltage; scalar_t__ set_current_limit; scalar_t__ set_voltage_sel; scalar_t__ set_voltage; scalar_t__ get_bypass; scalar_t__ get_status; scalar_t__ is_enabled; scalar_t__ get_mode; scalar_t__ get_current_limit; } ;
struct regulator_dev {scalar_t__ ena_pin; TYPE_1__* desc; } ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_46__ {struct attribute attr; } ;
struct TYPE_45__ {struct attribute attr; } ;
struct TYPE_44__ {struct attribute attr; } ;
struct TYPE_43__ {struct attribute attr; } ;
struct TYPE_42__ {struct attribute attr; } ;
struct TYPE_41__ {struct attribute attr; } ;
struct TYPE_40__ {struct attribute attr; } ;
struct TYPE_39__ {struct attribute attr; } ;
struct TYPE_38__ {struct attribute attr; } ;
struct TYPE_37__ {struct attribute attr; } ;
struct TYPE_36__ {struct attribute attr; } ;
struct TYPE_35__ {struct attribute attr; } ;
struct TYPE_34__ {int n_voltages; scalar_t__ fixed_uV; struct regulator_ops* ops; } ;
struct TYPE_33__ {struct attribute attr; } ;
struct TYPE_32__ {struct attribute attr; } ;
struct TYPE_31__ {struct attribute attr; } ;
struct TYPE_30__ {struct attribute attr; } ;
struct TYPE_29__ {struct attribute attr; } ;
struct TYPE_28__ {struct attribute attr; } ;
struct TYPE_27__ {struct attribute attr; } ;
struct TYPE_26__ {struct attribute attr; } ;
struct TYPE_25__ {struct attribute attr; } ;
struct TYPE_24__ {struct attribute attr; } ;

/* Variables and functions */
 TYPE_23__ dev_attr_bypass ; 
 TYPE_22__ dev_attr_max_microamps ; 
 TYPE_21__ dev_attr_max_microvolts ; 
 TYPE_20__ dev_attr_microamps ; 
 TYPE_19__ dev_attr_microvolts ; 
 TYPE_18__ dev_attr_min_microamps ; 
 TYPE_17__ dev_attr_min_microvolts ; 
 TYPE_16__ dev_attr_name ; 
 TYPE_15__ dev_attr_num_users ; 
 TYPE_14__ dev_attr_opmode ; 
 TYPE_13__ dev_attr_state ; 
 TYPE_12__ dev_attr_status ; 
 TYPE_11__ dev_attr_suspend_disk_microvolts ; 
 TYPE_10__ dev_attr_suspend_disk_mode ; 
 TYPE_9__ dev_attr_suspend_disk_state ; 
 TYPE_8__ dev_attr_suspend_mem_microvolts ; 
 TYPE_7__ dev_attr_suspend_mem_mode ; 
 TYPE_6__ dev_attr_suspend_mem_state ; 
 TYPE_5__ dev_attr_suspend_standby_microvolts ; 
 TYPE_4__ dev_attr_suspend_standby_mode ; 
 TYPE_3__ dev_attr_suspend_standby_state ; 
 TYPE_2__ dev_attr_type ; 
 struct regulator_dev* dev_to_rdev (struct device*) ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 scalar_t__ stub1 (struct regulator_dev*) ; 
 scalar_t__ stub2 (struct regulator_dev*) ; 
 scalar_t__ stub3 (struct regulator_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static umode_t regulator_attr_is_visible(struct kobject *kobj,
					 struct attribute *attr, int idx)
{
	struct device *dev = kobj_to_dev(kobj);
	struct regulator_dev *rdev = dev_to_rdev(dev);
	const struct regulator_ops *ops = rdev->desc->ops;
	umode_t mode = attr->mode;

	/* these three are always present */
	if (attr == &dev_attr_name.attr ||
	    attr == &dev_attr_num_users.attr ||
	    attr == &dev_attr_type.attr)
		return mode;

	/* some attributes need specific methods to be displayed */
	if (attr == &dev_attr_microvolts.attr) {
		if ((ops->get_voltage && ops->get_voltage(rdev) >= 0) ||
		    (ops->get_voltage_sel && ops->get_voltage_sel(rdev) >= 0) ||
		    (ops->list_voltage && ops->list_voltage(rdev, 0) >= 0) ||
		    (rdev->desc->fixed_uV && rdev->desc->n_voltages == 1))
			return mode;
		return 0;
	}

	if (attr == &dev_attr_microamps.attr)
		return ops->get_current_limit ? mode : 0;

	if (attr == &dev_attr_opmode.attr)
		return ops->get_mode ? mode : 0;

	if (attr == &dev_attr_state.attr)
		return (rdev->ena_pin || ops->is_enabled) ? mode : 0;

	if (attr == &dev_attr_status.attr)
		return ops->get_status ? mode : 0;

	if (attr == &dev_attr_bypass.attr)
		return ops->get_bypass ? mode : 0;

	/* constraints need specific supporting methods */
	if (attr == &dev_attr_min_microvolts.attr ||
	    attr == &dev_attr_max_microvolts.attr)
		return (ops->set_voltage || ops->set_voltage_sel) ? mode : 0;

	if (attr == &dev_attr_min_microamps.attr ||
	    attr == &dev_attr_max_microamps.attr)
		return ops->set_current_limit ? mode : 0;

	if (attr == &dev_attr_suspend_standby_state.attr ||
	    attr == &dev_attr_suspend_mem_state.attr ||
	    attr == &dev_attr_suspend_disk_state.attr)
		return mode;

	if (attr == &dev_attr_suspend_standby_microvolts.attr ||
	    attr == &dev_attr_suspend_mem_microvolts.attr ||
	    attr == &dev_attr_suspend_disk_microvolts.attr)
		return ops->set_suspend_voltage ? mode : 0;

	if (attr == &dev_attr_suspend_standby_mode.attr ||
	    attr == &dev_attr_suspend_mem_mode.attr ||
	    attr == &dev_attr_suspend_disk_mode.attr)
		return ops->set_suspend_mode ? mode : 0;

	return mode;
}