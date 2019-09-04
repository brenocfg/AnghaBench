#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_58__   TYPE_9__ ;
typedef  struct TYPE_57__   TYPE_8__ ;
typedef  struct TYPE_56__   TYPE_7__ ;
typedef  struct TYPE_55__   TYPE_6__ ;
typedef  struct TYPE_54__   TYPE_5__ ;
typedef  struct TYPE_53__   TYPE_4__ ;
typedef  struct TYPE_52__   TYPE_3__ ;
typedef  struct TYPE_51__   TYPE_2__ ;
typedef  struct TYPE_50__   TYPE_29__ ;
typedef  struct TYPE_49__   TYPE_28__ ;
typedef  struct TYPE_48__   TYPE_27__ ;
typedef  struct TYPE_47__   TYPE_26__ ;
typedef  struct TYPE_46__   TYPE_25__ ;
typedef  struct TYPE_45__   TYPE_24__ ;
typedef  struct TYPE_44__   TYPE_23__ ;
typedef  struct TYPE_43__   TYPE_22__ ;
typedef  struct TYPE_42__   TYPE_21__ ;
typedef  struct TYPE_41__   TYPE_20__ ;
typedef  struct TYPE_40__   TYPE_1__ ;
typedef  struct TYPE_39__   TYPE_19__ ;
typedef  struct TYPE_38__   TYPE_18__ ;
typedef  struct TYPE_37__   TYPE_17__ ;
typedef  struct TYPE_36__   TYPE_16__ ;
typedef  struct TYPE_35__   TYPE_15__ ;
typedef  struct TYPE_34__   TYPE_14__ ;
typedef  struct TYPE_33__   TYPE_13__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_32__ {TYPE_11__* pp_funcs; } ;
struct TYPE_51__ {int /*<<< orphan*/  dpm_enabled; scalar_t__ no_fan; } ;
struct amdgpu_device {int flags; TYPE_12__ powerplay; TYPE_2__ pm; } ;
struct TYPE_58__ {struct attribute attr; } ;
struct TYPE_57__ {struct attribute attr; } ;
struct TYPE_56__ {struct attribute attr; } ;
struct TYPE_55__ {struct attribute attr; } ;
struct TYPE_54__ {struct attribute attr; } ;
struct TYPE_53__ {struct attribute attr; } ;
struct TYPE_52__ {struct attribute attr; } ;
struct TYPE_40__ {struct attribute attr; } ;
struct TYPE_50__ {TYPE_1__ dev_attr; } ;
struct TYPE_35__ {struct attribute attr; } ;
struct TYPE_49__ {TYPE_15__ dev_attr; } ;
struct TYPE_36__ {struct attribute attr; } ;
struct TYPE_48__ {TYPE_16__ dev_attr; } ;
struct TYPE_47__ {TYPE_7__ dev_attr; } ;
struct TYPE_30__ {struct attribute attr; } ;
struct TYPE_46__ {TYPE_10__ dev_attr; } ;
struct TYPE_45__ {TYPE_8__ dev_attr; } ;
struct TYPE_44__ {TYPE_9__ dev_attr; } ;
struct TYPE_43__ {TYPE_5__ dev_attr; } ;
struct TYPE_42__ {TYPE_6__ dev_attr; } ;
struct TYPE_33__ {struct attribute attr; } ;
struct TYPE_41__ {TYPE_13__ dev_attr; } ;
struct TYPE_34__ {struct attribute attr; } ;
struct TYPE_39__ {TYPE_14__ dev_attr; } ;
struct TYPE_38__ {TYPE_3__ dev_attr; } ;
struct TYPE_37__ {TYPE_4__ dev_attr; } ;
struct TYPE_31__ {int /*<<< orphan*/  get_fan_speed_percent; int /*<<< orphan*/  set_fan_speed_percent; int /*<<< orphan*/  set_fan_control_mode; int /*<<< orphan*/  get_fan_control_mode; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  S_IWUSR ; 
 struct amdgpu_device* dev_get_drvdata (struct device*) ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 TYPE_29__ sensor_dev_attr_fan1_input ; 
 TYPE_28__ sensor_dev_attr_in1_input ; 
 TYPE_27__ sensor_dev_attr_in1_label ; 
 TYPE_26__ sensor_dev_attr_power1_average ; 
 TYPE_25__ sensor_dev_attr_power1_cap ; 
 TYPE_24__ sensor_dev_attr_power1_cap_max ; 
 TYPE_23__ sensor_dev_attr_power1_cap_min ; 
 TYPE_22__ sensor_dev_attr_pwm1 ; 
 TYPE_21__ sensor_dev_attr_pwm1_enable ; 
 TYPE_20__ sensor_dev_attr_pwm1_max ; 
 TYPE_19__ sensor_dev_attr_pwm1_min ; 
 TYPE_18__ sensor_dev_attr_temp1_crit ; 
 TYPE_17__ sensor_dev_attr_temp1_crit_hyst ; 

__attribute__((used)) static umode_t hwmon_attributes_visible(struct kobject *kobj,
					struct attribute *attr, int index)
{
	struct device *dev = kobj_to_dev(kobj);
	struct amdgpu_device *adev = dev_get_drvdata(dev);
	umode_t effective_mode = attr->mode;


	/* Skip fan attributes if fan is not present */
	if (adev->pm.no_fan && (attr == &sensor_dev_attr_pwm1.dev_attr.attr ||
	    attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr ||
	    attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_pwm1_min.dev_attr.attr ||
	    attr == &sensor_dev_attr_fan1_input.dev_attr.attr))
		return 0;

	/* Skip limit attributes if DPM is not enabled */
	if (!adev->pm.dpm_enabled &&
	    (attr == &sensor_dev_attr_temp1_crit.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp1_crit_hyst.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_min.dev_attr.attr))
		return 0;

	/* mask fan attributes if we have no bindings for this asic to expose */
	if ((!adev->powerplay.pp_funcs->get_fan_speed_percent &&
	     attr == &sensor_dev_attr_pwm1.dev_attr.attr) || /* can't query fan */
	    (!adev->powerplay.pp_funcs->get_fan_control_mode &&
	     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr)) /* can't query state */
		effective_mode &= ~S_IRUGO;

	if ((!adev->powerplay.pp_funcs->set_fan_speed_percent &&
	     attr == &sensor_dev_attr_pwm1.dev_attr.attr) || /* can't manage fan */
	    (!adev->powerplay.pp_funcs->set_fan_control_mode &&
	     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr)) /* can't manage state */
		effective_mode &= ~S_IWUSR;

	if ((adev->flags & AMD_IS_APU) &&
	    (attr == &sensor_dev_attr_power1_average.dev_attr.attr ||
	     attr == &sensor_dev_attr_power1_cap_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_power1_cap_min.dev_attr.attr||
	     attr == &sensor_dev_attr_power1_cap.dev_attr.attr))
		return 0;

	/* hide max/min values if we can't both query and manage the fan */
	if ((!adev->powerplay.pp_funcs->set_fan_speed_percent &&
	     !adev->powerplay.pp_funcs->get_fan_speed_percent) &&
	    (attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_min.dev_attr.attr))
		return 0;

	/* only APUs have vddnb */
	if (!(adev->flags & AMD_IS_APU) &&
	    (attr == &sensor_dev_attr_in1_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_in1_label.dev_attr.attr))
		return 0;

	return effective_mode;
}