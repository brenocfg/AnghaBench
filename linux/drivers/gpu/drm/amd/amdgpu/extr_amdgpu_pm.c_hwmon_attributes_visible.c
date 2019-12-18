#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_134__   TYPE_9__ ;
typedef  struct TYPE_133__   TYPE_8__ ;
typedef  struct TYPE_132__   TYPE_7__ ;
typedef  struct TYPE_131__   TYPE_6__ ;
typedef  struct TYPE_130__   TYPE_67__ ;
typedef  struct TYPE_129__   TYPE_66__ ;
typedef  struct TYPE_128__   TYPE_65__ ;
typedef  struct TYPE_127__   TYPE_64__ ;
typedef  struct TYPE_126__   TYPE_63__ ;
typedef  struct TYPE_125__   TYPE_62__ ;
typedef  struct TYPE_124__   TYPE_61__ ;
typedef  struct TYPE_123__   TYPE_60__ ;
typedef  struct TYPE_122__   TYPE_5__ ;
typedef  struct TYPE_121__   TYPE_59__ ;
typedef  struct TYPE_120__   TYPE_58__ ;
typedef  struct TYPE_119__   TYPE_57__ ;
typedef  struct TYPE_118__   TYPE_56__ ;
typedef  struct TYPE_117__   TYPE_55__ ;
typedef  struct TYPE_116__   TYPE_54__ ;
typedef  struct TYPE_115__   TYPE_53__ ;
typedef  struct TYPE_114__   TYPE_52__ ;
typedef  struct TYPE_113__   TYPE_51__ ;
typedef  struct TYPE_112__   TYPE_50__ ;
typedef  struct TYPE_111__   TYPE_4__ ;
typedef  struct TYPE_110__   TYPE_49__ ;
typedef  struct TYPE_109__   TYPE_48__ ;
typedef  struct TYPE_108__   TYPE_47__ ;
typedef  struct TYPE_107__   TYPE_46__ ;
typedef  struct TYPE_106__   TYPE_45__ ;
typedef  struct TYPE_105__   TYPE_44__ ;
typedef  struct TYPE_104__   TYPE_43__ ;
typedef  struct TYPE_103__   TYPE_42__ ;
typedef  struct TYPE_102__   TYPE_41__ ;
typedef  struct TYPE_101__   TYPE_40__ ;
typedef  struct TYPE_100__   TYPE_3__ ;
typedef  struct TYPE_99__   TYPE_39__ ;
typedef  struct TYPE_98__   TYPE_38__ ;
typedef  struct TYPE_97__   TYPE_37__ ;
typedef  struct TYPE_96__   TYPE_36__ ;
typedef  struct TYPE_95__   TYPE_35__ ;
typedef  struct TYPE_94__   TYPE_34__ ;
typedef  struct TYPE_93__   TYPE_33__ ;
typedef  struct TYPE_92__   TYPE_32__ ;
typedef  struct TYPE_91__   TYPE_31__ ;
typedef  struct TYPE_90__   TYPE_30__ ;
typedef  struct TYPE_89__   TYPE_2__ ;
typedef  struct TYPE_88__   TYPE_29__ ;
typedef  struct TYPE_87__   TYPE_28__ ;
typedef  struct TYPE_86__   TYPE_27__ ;
typedef  struct TYPE_85__   TYPE_26__ ;
typedef  struct TYPE_84__   TYPE_25__ ;
typedef  struct TYPE_83__   TYPE_24__ ;
typedef  struct TYPE_82__   TYPE_23__ ;
typedef  struct TYPE_81__   TYPE_22__ ;
typedef  struct TYPE_80__   TYPE_21__ ;
typedef  struct TYPE_79__   TYPE_20__ ;
typedef  struct TYPE_78__   TYPE_1__ ;
typedef  struct TYPE_77__   TYPE_19__ ;
typedef  struct TYPE_76__   TYPE_18__ ;
typedef  struct TYPE_75__   TYPE_17__ ;
typedef  struct TYPE_74__   TYPE_16__ ;
typedef  struct TYPE_73__   TYPE_15__ ;
typedef  struct TYPE_72__   TYPE_14__ ;
typedef  struct TYPE_71__   TYPE_13__ ;
typedef  struct TYPE_70__   TYPE_12__ ;
typedef  struct TYPE_69__   TYPE_11__ ;
typedef  struct TYPE_68__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_133__ {TYPE_7__* pp_funcs; } ;
struct TYPE_85__ {int /*<<< orphan*/  dpm_enabled; scalar_t__ no_fan; } ;
struct amdgpu_device {int flags; scalar_t__ family; scalar_t__ asic_type; TYPE_8__ powerplay; TYPE_26__ pm; } ;
struct TYPE_134__ {struct attribute attr; } ;
struct TYPE_132__ {int /*<<< orphan*/  get_fan_speed_rpm; int /*<<< orphan*/  set_fan_speed_rpm; int /*<<< orphan*/  get_fan_speed_percent; int /*<<< orphan*/  set_fan_speed_percent; int /*<<< orphan*/  set_fan_control_mode; int /*<<< orphan*/  get_fan_control_mode; } ;
struct TYPE_131__ {struct attribute attr; } ;
struct TYPE_86__ {struct attribute attr; } ;
struct TYPE_130__ {TYPE_27__ dev_attr; } ;
struct TYPE_92__ {struct attribute attr; } ;
struct TYPE_129__ {TYPE_32__ dev_attr; } ;
struct TYPE_94__ {struct attribute attr; } ;
struct TYPE_128__ {TYPE_34__ dev_attr; } ;
struct TYPE_93__ {struct attribute attr; } ;
struct TYPE_127__ {TYPE_33__ dev_attr; } ;
struct TYPE_95__ {struct attribute attr; } ;
struct TYPE_126__ {TYPE_35__ dev_attr; } ;
struct TYPE_71__ {struct attribute attr; } ;
struct TYPE_125__ {TYPE_13__ dev_attr; } ;
struct TYPE_72__ {struct attribute attr; } ;
struct TYPE_124__ {TYPE_14__ dev_attr; } ;
struct TYPE_123__ {TYPE_9__ dev_attr; } ;
struct TYPE_122__ {struct attribute attr; } ;
struct TYPE_68__ {struct attribute attr; } ;
struct TYPE_121__ {TYPE_10__ dev_attr; } ;
struct TYPE_69__ {struct attribute attr; } ;
struct TYPE_120__ {TYPE_11__ dev_attr; } ;
struct TYPE_70__ {struct attribute attr; } ;
struct TYPE_119__ {TYPE_12__ dev_attr; } ;
struct TYPE_100__ {struct attribute attr; } ;
struct TYPE_118__ {TYPE_3__ dev_attr; } ;
struct TYPE_117__ {TYPE_6__ dev_attr; } ;
struct TYPE_111__ {struct attribute attr; } ;
struct TYPE_116__ {TYPE_4__ dev_attr; } ;
struct TYPE_115__ {TYPE_5__ dev_attr; } ;
struct TYPE_87__ {struct attribute attr; } ;
struct TYPE_114__ {TYPE_28__ dev_attr; } ;
struct TYPE_88__ {struct attribute attr; } ;
struct TYPE_113__ {TYPE_29__ dev_attr; } ;
struct TYPE_90__ {struct attribute attr; } ;
struct TYPE_112__ {TYPE_30__ dev_attr; } ;
struct TYPE_91__ {struct attribute attr; } ;
struct TYPE_110__ {TYPE_31__ dev_attr; } ;
struct TYPE_78__ {struct attribute attr; } ;
struct TYPE_109__ {TYPE_1__ dev_attr; } ;
struct TYPE_89__ {struct attribute attr; } ;
struct TYPE_108__ {TYPE_2__ dev_attr; } ;
struct TYPE_77__ {struct attribute attr; } ;
struct TYPE_107__ {TYPE_19__ dev_attr; } ;
struct TYPE_73__ {struct attribute attr; } ;
struct TYPE_106__ {TYPE_15__ dev_attr; } ;
struct TYPE_74__ {struct attribute attr; } ;
struct TYPE_105__ {TYPE_16__ dev_attr; } ;
struct TYPE_79__ {struct attribute attr; } ;
struct TYPE_104__ {TYPE_20__ dev_attr; } ;
struct TYPE_81__ {struct attribute attr; } ;
struct TYPE_103__ {TYPE_22__ dev_attr; } ;
struct TYPE_83__ {struct attribute attr; } ;
struct TYPE_102__ {TYPE_24__ dev_attr; } ;
struct TYPE_75__ {struct attribute attr; } ;
struct TYPE_101__ {TYPE_17__ dev_attr; } ;
struct TYPE_76__ {struct attribute attr; } ;
struct TYPE_99__ {TYPE_18__ dev_attr; } ;
struct TYPE_80__ {struct attribute attr; } ;
struct TYPE_98__ {TYPE_21__ dev_attr; } ;
struct TYPE_82__ {struct attribute attr; } ;
struct TYPE_97__ {TYPE_23__ dev_attr; } ;
struct TYPE_84__ {struct attribute attr; } ;
struct TYPE_96__ {TYPE_25__ dev_attr; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FAMILY_KV ; 
 scalar_t__ AMDGPU_FAMILY_SI ; 
 int AMD_IS_APU ; 
 scalar_t__ CHIP_VEGA10 ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  S_IWUSR ; 
 struct amdgpu_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  is_support_sw_smu (struct amdgpu_device*) ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 TYPE_67__ sensor_dev_attr_fan1_enable ; 
 TYPE_66__ sensor_dev_attr_fan1_input ; 
 TYPE_65__ sensor_dev_attr_fan1_max ; 
 TYPE_64__ sensor_dev_attr_fan1_min ; 
 TYPE_63__ sensor_dev_attr_fan1_target ; 
 TYPE_62__ sensor_dev_attr_freq2_input ; 
 TYPE_61__ sensor_dev_attr_freq2_label ; 
 TYPE_60__ sensor_dev_attr_in0_input ; 
 TYPE_59__ sensor_dev_attr_in0_label ; 
 TYPE_58__ sensor_dev_attr_in1_input ; 
 TYPE_57__ sensor_dev_attr_in1_label ; 
 TYPE_56__ sensor_dev_attr_power1_average ; 
 TYPE_55__ sensor_dev_attr_power1_cap ; 
 TYPE_54__ sensor_dev_attr_power1_cap_max ; 
 TYPE_53__ sensor_dev_attr_power1_cap_min ; 
 TYPE_52__ sensor_dev_attr_pwm1 ; 
 TYPE_51__ sensor_dev_attr_pwm1_enable ; 
 TYPE_50__ sensor_dev_attr_pwm1_max ; 
 TYPE_49__ sensor_dev_attr_pwm1_min ; 
 TYPE_48__ sensor_dev_attr_temp1_crit ; 
 TYPE_47__ sensor_dev_attr_temp1_crit_hyst ; 
 TYPE_46__ sensor_dev_attr_temp1_emergency ; 
 TYPE_45__ sensor_dev_attr_temp2_crit ; 
 TYPE_44__ sensor_dev_attr_temp2_crit_hyst ; 
 TYPE_43__ sensor_dev_attr_temp2_emergency ; 
 TYPE_42__ sensor_dev_attr_temp2_input ; 
 TYPE_41__ sensor_dev_attr_temp2_label ; 
 TYPE_40__ sensor_dev_attr_temp3_crit ; 
 TYPE_39__ sensor_dev_attr_temp3_crit_hyst ; 
 TYPE_38__ sensor_dev_attr_temp3_emergency ; 
 TYPE_37__ sensor_dev_attr_temp3_input ; 
 TYPE_36__ sensor_dev_attr_temp3_label ; 

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
	    attr == &sensor_dev_attr_fan1_input.dev_attr.attr ||
	    attr == &sensor_dev_attr_fan1_min.dev_attr.attr ||
	    attr == &sensor_dev_attr_fan1_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_fan1_target.dev_attr.attr ||
	    attr == &sensor_dev_attr_fan1_enable.dev_attr.attr))
		return 0;

	/* Skip fan attributes on APU */
	if ((adev->flags & AMD_IS_APU) &&
	    (attr == &sensor_dev_attr_pwm1.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_min.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_min.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_target.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_enable.dev_attr.attr))
		return 0;

	/* Skip limit attributes if DPM is not enabled */
	if (!adev->pm.dpm_enabled &&
	    (attr == &sensor_dev_attr_temp1_crit.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp1_crit_hyst.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_min.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_min.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_target.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_enable.dev_attr.attr))
		return 0;

	if (!is_support_sw_smu(adev)) {
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
	}

	if (((adev->flags & AMD_IS_APU) ||
	     adev->family == AMDGPU_FAMILY_SI ||	/* not implemented yet */
	     adev->family == AMDGPU_FAMILY_KV) &&	/* not implemented yet */
	    (attr == &sensor_dev_attr_power1_average.dev_attr.attr ||
	     attr == &sensor_dev_attr_power1_cap_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_power1_cap_min.dev_attr.attr||
	     attr == &sensor_dev_attr_power1_cap.dev_attr.attr))
		return 0;

	if (!is_support_sw_smu(adev)) {
		/* hide max/min values if we can't both query and manage the fan */
		if ((!adev->powerplay.pp_funcs->set_fan_speed_percent &&
		     !adev->powerplay.pp_funcs->get_fan_speed_percent) &&
		     (!adev->powerplay.pp_funcs->set_fan_speed_rpm &&
		     !adev->powerplay.pp_funcs->get_fan_speed_rpm) &&
		    (attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
		     attr == &sensor_dev_attr_pwm1_min.dev_attr.attr))
			return 0;

		if ((!adev->powerplay.pp_funcs->set_fan_speed_rpm &&
		     !adev->powerplay.pp_funcs->get_fan_speed_rpm) &&
		    (attr == &sensor_dev_attr_fan1_max.dev_attr.attr ||
		     attr == &sensor_dev_attr_fan1_min.dev_attr.attr))
			return 0;
	}

	if ((adev->family == AMDGPU_FAMILY_SI ||	/* not implemented yet */
	     adev->family == AMDGPU_FAMILY_KV) &&	/* not implemented yet */
	    (attr == &sensor_dev_attr_in0_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_in0_label.dev_attr.attr))
		return 0;

	/* only APUs have vddnb */
	if (!(adev->flags & AMD_IS_APU) &&
	    (attr == &sensor_dev_attr_in1_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_in1_label.dev_attr.attr))
		return 0;

	/* no mclk on APUs */
	if ((adev->flags & AMD_IS_APU) &&
	    (attr == &sensor_dev_attr_freq2_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_freq2_label.dev_attr.attr))
		return 0;

	/* only SOC15 dGPUs support hotspot and mem temperatures */
	if (((adev->flags & AMD_IS_APU) ||
	     adev->asic_type < CHIP_VEGA10) &&
	    (attr == &sensor_dev_attr_temp2_crit.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp2_crit_hyst.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp3_crit.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp3_crit_hyst.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp1_emergency.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp2_emergency.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp3_emergency.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp2_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp3_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp2_label.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp3_label.dev_attr.attr))
		return 0;

	return effective_mode;
}