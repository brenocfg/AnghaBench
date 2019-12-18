#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct pm8941_wled {int /*<<< orphan*/  name; struct regmap* regmap; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct backlight_properties {int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness; int /*<<< orphan*/  type; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PM8941_WLED_DEFAULT_BRIGHTNESS ; 
 int /*<<< orphan*/  PM8941_WLED_REG_VAL_MAX ; 
 int PTR_ERR_OR_ZERO (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct regmap* dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct backlight_device* devm_backlight_device_register (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,struct pm8941_wled*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct pm8941_wled* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int pm8941_wled_configure (struct pm8941_wled*,TYPE_1__*) ; 
 int /*<<< orphan*/  pm8941_wled_ops ; 
 int pm8941_wled_setup (struct pm8941_wled*) ; 

__attribute__((used)) static int pm8941_wled_probe(struct platform_device *pdev)
{
	struct backlight_properties props;
	struct backlight_device *bl;
	struct pm8941_wled *wled;
	struct regmap *regmap;
	u32 val;
	int rc;

	regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!regmap) {
		dev_err(&pdev->dev, "Unable to get regmap\n");
		return -EINVAL;
	}

	wled = devm_kzalloc(&pdev->dev, sizeof(*wled), GFP_KERNEL);
	if (!wled)
		return -ENOMEM;

	wled->regmap = regmap;

	rc = pm8941_wled_configure(wled, &pdev->dev);
	if (rc)
		return rc;

	rc = pm8941_wled_setup(wled);
	if (rc)
		return rc;

	val = PM8941_WLED_DEFAULT_BRIGHTNESS;
	of_property_read_u32(pdev->dev.of_node, "default-brightness", &val);

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.brightness = val;
	props.max_brightness = PM8941_WLED_REG_VAL_MAX;
	bl = devm_backlight_device_register(&pdev->dev, wled->name,
					    &pdev->dev, wled,
					    &pm8941_wled_ops, &props);
	return PTR_ERR_OR_ZERO(bl);
}