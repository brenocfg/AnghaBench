#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct backlight_properties {void* max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_8__ {void* brightness; } ;
struct backlight_device {TYPE_2__ dev; TYPE_1__ props; } ;
struct adp5520_bl {TYPE_5__* pdata; int /*<<< orphan*/  master; int /*<<< orphan*/  lock; scalar_t__ current_brightness; int /*<<< orphan*/  id; } ;
struct TYPE_11__ {scalar_t__ en_ambl_sens; } ;

/* Variables and functions */
 void* ADP5020_MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  adp5520_bl_attr_group ; 
 int /*<<< orphan*/  adp5520_bl_ops ; 
 int adp5520_bl_setup (struct backlight_device*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 TYPE_5__* dev_get_platdata (TYPE_3__*) ; 
 struct backlight_device* devm_backlight_device_register (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adp5520_bl*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct adp5520_bl* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp5520_bl_probe(struct platform_device *pdev)
{
	struct backlight_properties props;
	struct backlight_device *bl;
	struct adp5520_bl *data;
	int ret = 0;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	data->master = pdev->dev.parent;
	data->pdata = dev_get_platdata(&pdev->dev);

	if (data->pdata  == NULL) {
		dev_err(&pdev->dev, "missing platform data\n");
		return -ENODEV;
	}

	data->id = pdev->id;
	data->current_brightness = 0;

	mutex_init(&data->lock);

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = ADP5020_MAX_BRIGHTNESS;
	bl = devm_backlight_device_register(&pdev->dev, pdev->name,
					data->master, data, &adp5520_bl_ops,
					&props);
	if (IS_ERR(bl)) {
		dev_err(&pdev->dev, "failed to register backlight\n");
		return PTR_ERR(bl);
	}

	bl->props.brightness = ADP5020_MAX_BRIGHTNESS;
	if (data->pdata->en_ambl_sens)
		ret = sysfs_create_group(&bl->dev.kobj,
			&adp5520_bl_attr_group);

	if (ret) {
		dev_err(&pdev->dev, "failed to register sysfs\n");
		return ret;
	}

	platform_set_drvdata(pdev, bl);
	ret = adp5520_bl_setup(bl);
	if (ret) {
		dev_err(&pdev->dev, "failed to setup\n");
		if (data->pdata->en_ambl_sens)
			sysfs_remove_group(&bl->dev.kobj,
					&adp5520_bl_attr_group);
		return ret;
	}

	backlight_update_status(bl);

	return 0;
}