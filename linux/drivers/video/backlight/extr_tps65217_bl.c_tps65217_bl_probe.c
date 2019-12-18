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
struct TYPE_6__ {int /*<<< orphan*/  brightness; } ;
struct tps65217_bl_pdata {int /*<<< orphan*/  dft_brightness; TYPE_1__ props; } ;
struct tps65217_bl {int is_enabled; struct tps65217_bl_pdata* bl; TYPE_2__* dev; struct tps65217* tps; } ;
struct tps65217 {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_2__ dev; } ;
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct tps65217_bl_pdata*) ; 
 int PTR_ERR (struct tps65217_bl_pdata*) ; 
 int /*<<< orphan*/  backlight_update_status (struct tps65217_bl_pdata*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct tps65217* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct tps65217_bl_pdata* devm_backlight_device_register (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,struct tps65217_bl*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct tps65217_bl* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tps65217_bl*) ; 
 int tps65217_bl_hw_init (struct tps65217_bl*,struct tps65217_bl_pdata*) ; 
 int /*<<< orphan*/  tps65217_bl_ops ; 
 struct tps65217_bl_pdata* tps65217_bl_parse_dt (struct platform_device*) ; 

__attribute__((used)) static int tps65217_bl_probe(struct platform_device *pdev)
{
	int rc;
	struct tps65217 *tps = dev_get_drvdata(pdev->dev.parent);
	struct tps65217_bl *tps65217_bl;
	struct tps65217_bl_pdata *pdata;
	struct backlight_properties bl_props;

	pdata = tps65217_bl_parse_dt(pdev);
	if (IS_ERR(pdata))
		return PTR_ERR(pdata);

	tps65217_bl = devm_kzalloc(&pdev->dev, sizeof(*tps65217_bl),
				GFP_KERNEL);
	if (tps65217_bl == NULL)
		return -ENOMEM;

	tps65217_bl->tps = tps;
	tps65217_bl->dev = &pdev->dev;
	tps65217_bl->is_enabled = false;

	rc = tps65217_bl_hw_init(tps65217_bl, pdata);
	if (rc)
		return rc;

	memset(&bl_props, 0, sizeof(struct backlight_properties));
	bl_props.type = BACKLIGHT_RAW;
	bl_props.max_brightness = 100;

	tps65217_bl->bl = devm_backlight_device_register(&pdev->dev, pdev->name,
						tps65217_bl->dev, tps65217_bl,
						&tps65217_bl_ops, &bl_props);
	if (IS_ERR(tps65217_bl->bl)) {
		dev_err(tps65217_bl->dev,
			"registration of backlight device failed: %d\n", rc);
		return PTR_ERR(tps65217_bl->bl);
	}

	tps65217_bl->bl->props.brightness = pdata->dft_brightness;
	backlight_update_status(tps65217_bl->bl);
	platform_set_drvdata(pdev, tps65217_bl);

	return 0;
}