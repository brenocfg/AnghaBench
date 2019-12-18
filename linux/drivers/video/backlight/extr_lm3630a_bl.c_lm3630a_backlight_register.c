#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lm3630a_platform_data {scalar_t__ leda_ctrl; char* leda_label; scalar_t__ ledb_ctrl; char* ledb_label; int /*<<< orphan*/  ledb_max_brt; int /*<<< orphan*/  ledb_init_brt; int /*<<< orphan*/  leda_max_brt; int /*<<< orphan*/  leda_init_brt; } ;
struct lm3630a_chip {void* bledb; int /*<<< orphan*/  dev; void* bleda; struct lm3630a_platform_data* pdata; } ;
struct backlight_properties {int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ LM3630A_LEDA_DISABLE ; 
 scalar_t__ LM3630A_LEDB_DISABLE ; 
 scalar_t__ LM3630A_LEDB_ON_A ; 
 int PTR_ERR (void*) ; 
 void* devm_backlight_device_register (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct lm3630a_chip*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  lm3630a_bank_a_ops ; 
 int /*<<< orphan*/  lm3630a_bank_b_ops ; 

__attribute__((used)) static int lm3630a_backlight_register(struct lm3630a_chip *pchip)
{
	struct lm3630a_platform_data *pdata = pchip->pdata;
	struct backlight_properties props;
	const char *label;

	props.type = BACKLIGHT_RAW;
	if (pdata->leda_ctrl != LM3630A_LEDA_DISABLE) {
		props.brightness = pdata->leda_init_brt;
		props.max_brightness = pdata->leda_max_brt;
		label = pdata->leda_label ? pdata->leda_label : "lm3630a_leda";
		pchip->bleda =
		    devm_backlight_device_register(pchip->dev, label,
						   pchip->dev, pchip,
						   &lm3630a_bank_a_ops, &props);
		if (IS_ERR(pchip->bleda))
			return PTR_ERR(pchip->bleda);
	}

	if ((pdata->ledb_ctrl != LM3630A_LEDB_DISABLE) &&
	    (pdata->ledb_ctrl != LM3630A_LEDB_ON_A)) {
		props.brightness = pdata->ledb_init_brt;
		props.max_brightness = pdata->ledb_max_brt;
		label = pdata->ledb_label ? pdata->ledb_label : "lm3630a_ledb";
		pchip->bledb =
		    devm_backlight_device_register(pchip->dev, label,
						   pchip->dev, pchip,
						   &lm3630a_bank_b_ops, &props);
		if (IS_ERR(pchip->bledb))
			return PTR_ERR(pchip->bledb);
	}
	return 0;
}