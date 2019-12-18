#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/ * dev; } ;
struct ls037v7dw01_panel {TYPE_1__ panel; void* ud_gpio; void* lr_gpio; void* mo_gpio; void* resb_gpio; void* ini_gpio; void* vdd; struct platform_device* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_index (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 struct ls037v7dw01_panel* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  ls037v7dw01_funcs ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ls037v7dw01_panel*) ; 

__attribute__((used)) static int ls037v7dw01_probe(struct platform_device *pdev)
{
	struct ls037v7dw01_panel *lcd;

	lcd = devm_kzalloc(&pdev->dev, sizeof(*lcd), GFP_KERNEL);
	if (!lcd)
		return -ENOMEM;

	platform_set_drvdata(pdev, lcd);
	lcd->pdev = pdev;

	lcd->vdd = devm_regulator_get(&pdev->dev, "envdd");
	if (IS_ERR(lcd->vdd)) {
		dev_err(&pdev->dev, "failed to get regulator\n");
		return PTR_ERR(lcd->vdd);
	}

	lcd->ini_gpio = devm_gpiod_get(&pdev->dev, "enable", GPIOD_OUT_LOW);
	if (IS_ERR(lcd->ini_gpio)) {
		dev_err(&pdev->dev, "failed to get enable gpio\n");
		return PTR_ERR(lcd->ini_gpio);
	}

	lcd->resb_gpio = devm_gpiod_get(&pdev->dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(lcd->resb_gpio)) {
		dev_err(&pdev->dev, "failed to get reset gpio\n");
		return PTR_ERR(lcd->resb_gpio);
	}

	lcd->mo_gpio = devm_gpiod_get_index(&pdev->dev, "mode", 0,
					    GPIOD_OUT_LOW);
	if (IS_ERR(lcd->mo_gpio)) {
		dev_err(&pdev->dev, "failed to get mode[0] gpio\n");
		return PTR_ERR(lcd->mo_gpio);
	}

	lcd->lr_gpio = devm_gpiod_get_index(&pdev->dev, "mode", 1,
					    GPIOD_OUT_LOW);
	if (IS_ERR(lcd->lr_gpio)) {
		dev_err(&pdev->dev, "failed to get mode[1] gpio\n");
		return PTR_ERR(lcd->lr_gpio);
	}

	lcd->ud_gpio = devm_gpiod_get_index(&pdev->dev, "mode", 2,
					    GPIOD_OUT_LOW);
	if (IS_ERR(lcd->ud_gpio)) {
		dev_err(&pdev->dev, "failed to get mode[2] gpio\n");
		return PTR_ERR(lcd->ud_gpio);
	}

	drm_panel_init(&lcd->panel);
	lcd->panel.dev = &pdev->dev;
	lcd->panel.funcs = &ls037v7dw01_funcs;

	return drm_panel_add(&lcd->panel);
}