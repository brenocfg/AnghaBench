#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wm831x_status_pdata {int default_src; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  groups; int /*<<< orphan*/  blink_set; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct wm831x_status {int reg_val; int src; TYPE_1__ cdev; int /*<<< orphan*/  brightness; int /*<<< orphan*/  reg; int /*<<< orphan*/  value_lock; int /*<<< orphan*/  mutex; struct wm831x* wm831x; } ;
struct wm831x_pdata {scalar_t__* status; } ;
struct wm831x {int /*<<< orphan*/  dev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int id; TYPE_2__ dev; } ;
typedef  int /*<<< orphan*/  pdata ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_REG ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int WM831X_LED_MODE_MASK ; 
 int WM831X_LED_SRC_MASK ; 
 int WM831X_LED_SRC_SHIFT ; 
 int WM831X_STATUS_PRESERVE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct wm831x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct wm831x_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 struct wm831x_status* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (struct wm831x_status_pdata*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct wm831x_status_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm831x_status_blink_set ; 
 int /*<<< orphan*/  wm831x_status_brightness_set ; 
 int /*<<< orphan*/  wm831x_status_groups ; 

__attribute__((used)) static int wm831x_status_probe(struct platform_device *pdev)
{
	struct wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	struct wm831x_pdata *chip_pdata;
	struct wm831x_status_pdata pdata;
	struct wm831x_status *drvdata;
	struct resource *res;
	int id = pdev->id % ARRAY_SIZE(chip_pdata->status);
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_REG, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "No register resource\n");
		return -EINVAL;
	}

	drvdata = devm_kzalloc(&pdev->dev, sizeof(struct wm831x_status),
			       GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	drvdata->wm831x = wm831x;
	drvdata->reg = res->start;

	if (dev_get_platdata(wm831x->dev))
		chip_pdata = dev_get_platdata(wm831x->dev);
	else
		chip_pdata = NULL;

	memset(&pdata, 0, sizeof(pdata));
	if (chip_pdata && chip_pdata->status[id])
		memcpy(&pdata, chip_pdata->status[id], sizeof(pdata));
	else
		pdata.name = dev_name(&pdev->dev);

	mutex_init(&drvdata->mutex);
	spin_lock_init(&drvdata->value_lock);

	/* We cache the configuration register and read startup values
	 * from it. */
	drvdata->reg_val = wm831x_reg_read(wm831x, drvdata->reg);

	if (drvdata->reg_val & WM831X_LED_MODE_MASK)
		drvdata->brightness = LED_FULL;
	else
		drvdata->brightness = LED_OFF;

	/* Set a default source if configured, otherwise leave the
	 * current hardware setting.
	 */
	if (pdata.default_src == WM831X_STATUS_PRESERVE) {
		drvdata->src = drvdata->reg_val;
		drvdata->src &= WM831X_LED_SRC_MASK;
		drvdata->src >>= WM831X_LED_SRC_SHIFT;
	} else {
		drvdata->src = pdata.default_src - 1;
	}

	drvdata->cdev.name = pdata.name;
	drvdata->cdev.default_trigger = pdata.default_trigger;
	drvdata->cdev.brightness_set_blocking = wm831x_status_brightness_set;
	drvdata->cdev.blink_set = wm831x_status_blink_set;
	drvdata->cdev.groups = wm831x_status_groups;

	ret = devm_led_classdev_register(wm831x->dev, &drvdata->cdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register LED: %d\n", ret);
		return ret;
	}

	return 0;
}