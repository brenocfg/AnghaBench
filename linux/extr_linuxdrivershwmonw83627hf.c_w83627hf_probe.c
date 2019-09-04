#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_66__   TYPE_9__ ;
typedef  struct TYPE_65__   TYPE_8__ ;
typedef  struct TYPE_64__   TYPE_7__ ;
typedef  struct TYPE_63__   TYPE_6__ ;
typedef  struct TYPE_62__   TYPE_5__ ;
typedef  struct TYPE_61__   TYPE_4__ ;
typedef  struct TYPE_60__   TYPE_3__ ;
typedef  struct TYPE_59__   TYPE_33__ ;
typedef  struct TYPE_58__   TYPE_32__ ;
typedef  struct TYPE_57__   TYPE_31__ ;
typedef  struct TYPE_56__   TYPE_30__ ;
typedef  struct TYPE_55__   TYPE_2__ ;
typedef  struct TYPE_54__   TYPE_29__ ;
typedef  struct TYPE_53__   TYPE_28__ ;
typedef  struct TYPE_52__   TYPE_27__ ;
typedef  struct TYPE_51__   TYPE_26__ ;
typedef  struct TYPE_50__   TYPE_25__ ;
typedef  struct TYPE_49__   TYPE_24__ ;
typedef  struct TYPE_48__   TYPE_23__ ;
typedef  struct TYPE_47__   TYPE_22__ ;
typedef  struct TYPE_46__   TYPE_21__ ;
typedef  struct TYPE_45__   TYPE_20__ ;
typedef  struct TYPE_44__   TYPE_1__ ;
typedef  struct TYPE_43__   TYPE_19__ ;
typedef  struct TYPE_42__   TYPE_18__ ;
typedef  struct TYPE_41__   TYPE_17__ ;
typedef  struct TYPE_40__   TYPE_16__ ;
typedef  struct TYPE_39__   TYPE_15__ ;
typedef  struct TYPE_38__   TYPE_14__ ;
typedef  struct TYPE_37__   TYPE_13__ ;
typedef  struct TYPE_36__   TYPE_12__ ;
typedef  struct TYPE_35__   TYPE_11__ ;
typedef  struct TYPE_34__   TYPE_10__ ;

/* Type definitions */
struct w83627hf_sio_data {scalar_t__ type; } ;
struct w83627hf_data {int addr; scalar_t__ type; char const* name; int vid; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  vrm; int /*<<< orphan*/ * fan_min; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  lock; } ;
struct resource {int start; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct platform_device {struct device dev; } ;
struct TYPE_66__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_65__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_64__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_63__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_62__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_61__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_60__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_59__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_58__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_57__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_56__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_55__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_54__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_53__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_52__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_51__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_50__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_49__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_48__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_47__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_46__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_45__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_44__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_43__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_42__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_41__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_40__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_39__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_38__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_37__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_36__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_35__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_34__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRVNAME ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W83627HF_REG_FAN_MIN (int) ; 
 int WINB_REGION_SIZE ; 
 int /*<<< orphan*/  dev_attr_cpu0_vid ; 
 int /*<<< orphan*/  dev_attr_vrm ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned long,unsigned long) ; 
 struct w83627hf_sio_data* dev_get_platdata (struct device*) ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 struct w83627hf_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_region (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (struct device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct w83627hf_data*) ; 
 TYPE_33__ sensor_dev_attr_fan3_alarm ; 
 TYPE_32__ sensor_dev_attr_fan3_beep ; 
 TYPE_31__ sensor_dev_attr_fan3_div ; 
 TYPE_30__ sensor_dev_attr_fan3_input ; 
 TYPE_29__ sensor_dev_attr_fan3_min ; 
 TYPE_28__ sensor_dev_attr_in1_alarm ; 
 TYPE_27__ sensor_dev_attr_in1_beep ; 
 TYPE_26__ sensor_dev_attr_in1_input ; 
 TYPE_25__ sensor_dev_attr_in1_max ; 
 TYPE_24__ sensor_dev_attr_in1_min ; 
 TYPE_23__ sensor_dev_attr_in5_alarm ; 
 TYPE_22__ sensor_dev_attr_in5_beep ; 
 TYPE_21__ sensor_dev_attr_in5_input ; 
 TYPE_20__ sensor_dev_attr_in5_max ; 
 TYPE_19__ sensor_dev_attr_in5_min ; 
 TYPE_18__ sensor_dev_attr_in6_alarm ; 
 TYPE_17__ sensor_dev_attr_in6_beep ; 
 TYPE_16__ sensor_dev_attr_in6_input ; 
 TYPE_15__ sensor_dev_attr_in6_max ; 
 TYPE_14__ sensor_dev_attr_in6_min ; 
 TYPE_13__ sensor_dev_attr_pwm1_enable ; 
 TYPE_12__ sensor_dev_attr_pwm1_freq ; 
 TYPE_11__ sensor_dev_attr_pwm2_enable ; 
 TYPE_10__ sensor_dev_attr_pwm2_freq ; 
 TYPE_9__ sensor_dev_attr_pwm3 ; 
 TYPE_8__ sensor_dev_attr_pwm3_enable ; 
 TYPE_7__ sensor_dev_attr_pwm3_freq ; 
 TYPE_6__ sensor_dev_attr_temp3_alarm ; 
 TYPE_5__ sensor_dev_attr_temp3_beep ; 
 TYPE_4__ sensor_dev_attr_temp3_input ; 
 TYPE_3__ sensor_dev_attr_temp3_max ; 
 TYPE_2__ sensor_dev_attr_temp3_max_hyst ; 
 TYPE_1__ sensor_dev_attr_temp3_type ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vid_which_vrm () ; 
 scalar_t__ w83627hf ; 
 int /*<<< orphan*/  w83627hf_group ; 
 int /*<<< orphan*/  w83627hf_group_opt ; 
 int /*<<< orphan*/  w83627hf_init_device (struct platform_device*) ; 
 int /*<<< orphan*/  w83627hf_read_value (struct w83627hf_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83627hf_update_fan_div (struct w83627hf_data*) ; 
 scalar_t__ w83627thf ; 
 scalar_t__ w83637hf ; 
 scalar_t__ w83687thf ; 
 scalar_t__ w83697hf ; 

__attribute__((used)) static int w83627hf_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct w83627hf_sio_data *sio_data = dev_get_platdata(dev);
	struct w83627hf_data *data;
	struct resource *res;
	int err, i;

	static const char *names[] = {
		"w83627hf",
		"w83627thf",
		"w83697hf",
		"w83637hf",
		"w83687thf",
	};

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!devm_request_region(dev, res->start, WINB_REGION_SIZE, DRVNAME)) {
		dev_err(dev, "Failed to request region 0x%lx-0x%lx\n",
			(unsigned long)res->start,
			(unsigned long)(res->start + WINB_REGION_SIZE - 1));
		return -EBUSY;
	}

	data = devm_kzalloc(dev, sizeof(struct w83627hf_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->addr = res->start;
	data->type = sio_data->type;
	data->name = names[sio_data->type];
	mutex_init(&data->lock);
	mutex_init(&data->update_lock);
	platform_set_drvdata(pdev, data);

	/* Initialize the chip */
	w83627hf_init_device(pdev);

	/* A few vars need to be filled upon startup */
	for (i = 0; i <= 2; i++)
		data->fan_min[i] = w83627hf_read_value(
					data, W83627HF_REG_FAN_MIN(i));
	w83627hf_update_fan_div(data);

	/* Register common device attributes */
	err = sysfs_create_group(&dev->kobj, &w83627hf_group);
	if (err)
		return err;

	/* Register chip-specific device attributes */
	if (data->type == w83627hf || data->type == w83697hf)
		if ((err = device_create_file(dev,
				&sensor_dev_attr_in5_input.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in5_min.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in5_max.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in5_alarm.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in5_beep.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in6_input.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in6_min.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in6_max.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in6_alarm.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in6_beep.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_pwm1_freq.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_pwm2_freq.dev_attr)))
			goto error;

	if (data->type != w83697hf)
		if ((err = device_create_file(dev,
				&sensor_dev_attr_in1_input.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in1_min.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in1_max.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in1_alarm.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_in1_beep.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_fan3_input.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_fan3_min.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_fan3_div.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_fan3_alarm.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_fan3_beep.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_input.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_max.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_max_hyst.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_alarm.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_beep.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_type.dev_attr)))
			goto error;

	if (data->type != w83697hf && data->vid != 0xff) {
		/* Convert VID to voltage based on VRM */
		data->vrm = vid_which_vrm();

		if ((err = device_create_file(dev, &dev_attr_cpu0_vid))
		 || (err = device_create_file(dev, &dev_attr_vrm)))
			goto error;
	}

	if (data->type == w83627thf || data->type == w83637hf
	    || data->type == w83687thf) {
		err = device_create_file(dev, &sensor_dev_attr_pwm3.dev_attr);
		if (err)
			goto error;
	}

	if (data->type == w83637hf || data->type == w83687thf)
		if ((err = device_create_file(dev,
				&sensor_dev_attr_pwm1_freq.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_pwm2_freq.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_pwm3_freq.dev_attr)))
			goto error;

	if (data->type != w83627hf)
		if ((err = device_create_file(dev,
				&sensor_dev_attr_pwm1_enable.dev_attr))
		 || (err = device_create_file(dev,
				&sensor_dev_attr_pwm2_enable.dev_attr)))
			goto error;

	if (data->type == w83627thf || data->type == w83637hf
	    || data->type == w83687thf) {
		err = device_create_file(dev,
					 &sensor_dev_attr_pwm3_enable.dev_attr);
		if (err)
			goto error;
	}

	data->hwmon_dev = hwmon_device_register(dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto error;
	}

	return 0;

 error:
	sysfs_remove_group(&dev->kobj, &w83627hf_group);
	sysfs_remove_group(&dev->kobj, &w83627hf_group_opt);
	return err;
}