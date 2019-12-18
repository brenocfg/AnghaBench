#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int id; TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct da903x_backlight_data {int id; int /*<<< orphan*/  da903x_dev; scalar_t__ current_brightness; } ;
struct da9034_backlight_pdata {int /*<<< orphan*/  output_current; } ;
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
typedef  int /*<<< orphan*/  props ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
#define  DA9030_ID_WLED 129 
 int DA9030_MAX_BRIGHTNESS ; 
#define  DA9034_ID_WLED 128 
 int DA9034_MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  DA9034_WLED_CONTROL2 ; 
 int /*<<< orphan*/  DA9034_WLED_ISET (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  da903x_backlight_ops ; 
 int /*<<< orphan*/  da903x_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct da9034_backlight_pdata* dev_get_platdata (TYPE_2__*) ; 
 struct backlight_device* devm_backlight_device_register (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct da903x_backlight_data*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct da903x_backlight_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 

__attribute__((used)) static int da903x_backlight_probe(struct platform_device *pdev)
{
	struct da9034_backlight_pdata *pdata = dev_get_platdata(&pdev->dev);
	struct da903x_backlight_data *data;
	struct backlight_device *bl;
	struct backlight_properties props;
	int max_brightness;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	switch (pdev->id) {
	case DA9030_ID_WLED:
		max_brightness = DA9030_MAX_BRIGHTNESS;
		break;
	case DA9034_ID_WLED:
		max_brightness = DA9034_MAX_BRIGHTNESS;
		break;
	default:
		dev_err(&pdev->dev, "invalid backlight device ID(%d)\n",
				pdev->id);
		return -EINVAL;
	}

	data->id = pdev->id;
	data->da903x_dev = pdev->dev.parent;
	data->current_brightness = 0;

	/* adjust the WLED output current */
	if (pdata)
		da903x_write(data->da903x_dev, DA9034_WLED_CONTROL2,
				DA9034_WLED_ISET(pdata->output_current));

	memset(&props, 0, sizeof(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = max_brightness;
	bl = devm_backlight_device_register(&pdev->dev, pdev->name,
					data->da903x_dev, data,
					&da903x_backlight_ops, &props);
	if (IS_ERR(bl)) {
		dev_err(&pdev->dev, "failed to register backlight\n");
		return PTR_ERR(bl);
	}

	bl->props.brightness = max_brightness;

	platform_set_drvdata(pdev, bl);
	backlight_update_status(bl);
	return 0;
}