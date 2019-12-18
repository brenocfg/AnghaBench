#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lcd_platform_data {int /*<<< orphan*/  reset_delay; int /*<<< orphan*/  (* reset ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  power_on_delay; int /*<<< orphan*/  (* power_on ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct ams369fg06 {int /*<<< orphan*/  dev; int /*<<< orphan*/  ld; struct backlight_device* bd; struct lcd_platform_data* lcd_pd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ams369fg06_gamma_ctl (struct ams369fg06*,int /*<<< orphan*/ ) ; 
 int ams369fg06_ldi_enable (struct ams369fg06*) ; 
 int ams369fg06_ldi_init (struct ams369fg06*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ams369fg06_power_on(struct ams369fg06 *lcd)
{
	int ret = 0;
	struct lcd_platform_data *pd;
	struct backlight_device *bd;

	pd = lcd->lcd_pd;
	bd = lcd->bd;

	if (pd->power_on) {
		pd->power_on(lcd->ld, 1);
		msleep(pd->power_on_delay);
	}

	if (!pd->reset) {
		dev_err(lcd->dev, "reset is NULL.\n");
		return -EINVAL;
	}

	pd->reset(lcd->ld);
	msleep(pd->reset_delay);

	ret = ams369fg06_ldi_init(lcd);
	if (ret) {
		dev_err(lcd->dev, "failed to initialize ldi.\n");
		return ret;
	}

	ret = ams369fg06_ldi_enable(lcd);
	if (ret) {
		dev_err(lcd->dev, "failed to enable ldi.\n");
		return ret;
	}

	/* set brightness to current value after power on or resume. */
	ret = ams369fg06_gamma_ctl(lcd, bd->props.brightness);
	if (ret) {
		dev_err(lcd->dev, "lcd gamma setting failed.\n");
		return ret;
	}

	return 0;
}