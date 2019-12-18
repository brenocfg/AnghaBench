#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct as3711_bl_data {int /*<<< orphan*/  type; } ;
struct as3711_bl_supply {struct as3711_bl_data su2; struct as3711_bl_data su1; struct as3711_bl_pdata* pdata; struct as3711* as3711; } ;
struct as3711_bl_pdata {int su2_fbprot; int su2_feedback; int su1_max_uA; int su2_max_uA; scalar_t__ su2_fb; scalar_t__ su1_fb; } ;
struct as3711 {int dummy; } ;
struct TYPE_8__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS3711_BL_SU1 ; 
 int /*<<< orphan*/  AS3711_BL_SU2 ; 
#define  AS3711_SU2_CURR1 136 
#define  AS3711_SU2_CURR2 135 
#define  AS3711_SU2_CURR3 134 
#define  AS3711_SU2_CURR_AUTO 133 
#define  AS3711_SU2_GPIO2 132 
#define  AS3711_SU2_GPIO3 131 
#define  AS3711_SU2_GPIO4 130 
#define  AS3711_SU2_LX_SD4 129 
#define  AS3711_SU2_VOLTAGE 128 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int as3711_backlight_parse_dt (TYPE_1__*) ; 
 int as3711_bl_init_su2 (struct as3711_bl_supply*) ; 
 int as3711_bl_register (struct platform_device*,unsigned int,struct as3711_bl_data*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct as3711* dev_get_drvdata (TYPE_4__*) ; 
 struct as3711_bl_pdata* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 struct as3711_bl_supply* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 unsigned int min (int,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct as3711_bl_supply*) ; 

__attribute__((used)) static int as3711_backlight_probe(struct platform_device *pdev)
{
	struct as3711_bl_pdata *pdata = dev_get_platdata(&pdev->dev);
	struct as3711 *as3711 = dev_get_drvdata(pdev->dev.parent);
	struct as3711_bl_supply *supply;
	struct as3711_bl_data *su;
	unsigned int max_brightness;
	int ret;

	if (!pdata) {
		dev_err(&pdev->dev, "No platform data, exiting...\n");
		return -ENODEV;
	}

	if (pdev->dev.parent->of_node) {
		ret = as3711_backlight_parse_dt(&pdev->dev);
		if (ret < 0) {
			dev_err(&pdev->dev, "DT parsing failed: %d\n", ret);
			return ret;
		}
	}

	if (!pdata->su1_fb && !pdata->su2_fb) {
		dev_err(&pdev->dev, "No framebuffer specified\n");
		return -EINVAL;
	}

	/*
	 * Due to possible hardware damage I chose to block all modes,
	 * unsupported on my hardware. Anyone, wishing to use any of those modes
	 * will have to first review the code, then activate and test it.
	 */
	if (pdata->su1_fb ||
	    pdata->su2_fbprot != AS3711_SU2_GPIO4 ||
	    pdata->su2_feedback != AS3711_SU2_CURR_AUTO) {
		dev_warn(&pdev->dev,
			 "Attention! An untested mode has been chosen!\n"
			 "Please, review the code, enable, test, and report success:-)\n");
		return -EINVAL;
	}

	supply = devm_kzalloc(&pdev->dev, sizeof(*supply), GFP_KERNEL);
	if (!supply)
		return -ENOMEM;

	supply->as3711 = as3711;
	supply->pdata = pdata;

	if (pdata->su1_fb) {
		su = &supply->su1;
		su->type = AS3711_BL_SU1;

		max_brightness = min(pdata->su1_max_uA, 31);
		ret = as3711_bl_register(pdev, max_brightness, su);
		if (ret < 0)
			return ret;
	}

	if (pdata->su2_fb) {
		su = &supply->su2;
		su->type = AS3711_BL_SU2;

		switch (pdata->su2_fbprot) {
		case AS3711_SU2_GPIO2:
		case AS3711_SU2_GPIO3:
		case AS3711_SU2_GPIO4:
		case AS3711_SU2_LX_SD4:
			break;
		default:
			return -EINVAL;
		}

		switch (pdata->su2_feedback) {
		case AS3711_SU2_VOLTAGE:
			max_brightness = min(pdata->su2_max_uA, 31);
			break;
		case AS3711_SU2_CURR1:
		case AS3711_SU2_CURR2:
		case AS3711_SU2_CURR3:
		case AS3711_SU2_CURR_AUTO:
			max_brightness = min(pdata->su2_max_uA / 150, 255);
			break;
		default:
			return -EINVAL;
		}

		ret = as3711_bl_init_su2(supply);
		if (ret < 0)
			return ret;

		ret = as3711_bl_register(pdev, max_brightness, su);
		if (ret < 0)
			return ret;
	}

	platform_set_drvdata(pdev, supply);

	return 0;
}