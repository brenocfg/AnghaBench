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
struct twl4030_platform_data {int /*<<< orphan*/ * power; int /*<<< orphan*/ * bci; int /*<<< orphan*/  vaux4; int /*<<< orphan*/  vaux3; int /*<<< orphan*/  vaux1; int /*<<< orphan*/  vsim; int /*<<< orphan*/  vmmc2; int /*<<< orphan*/  vpll2; int /*<<< orphan*/  vintdig; int /*<<< orphan*/  vintana2; int /*<<< orphan*/  vintana1; int /*<<< orphan*/  vaux2; int /*<<< orphan*/  vdac; int /*<<< orphan*/  vmmc1; int /*<<< orphan*/  vdd2; int /*<<< orphan*/  vdd1; int /*<<< orphan*/  vio; int /*<<< orphan*/  vpll1; int /*<<< orphan*/ * audio; int /*<<< orphan*/ * usb; int /*<<< orphan*/ * madc; int /*<<< orphan*/ * keypad; int /*<<< orphan*/ * gpio; } ;
struct TYPE_2__ {int valid_modes_mask; int valid_ops_mask; } ;
struct regulator_init_data {TYPE_1__ constraints; } ;
struct regulator_consumer_supply {char* supply; void* dev_name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int BCI_INTR_OFFSET ; 
 unsigned int BCI_PRES_INTR_OFFSET ; 
 int /*<<< orphan*/  CONFIG_CHARGER_TWL4030 ; 
 int /*<<< orphan*/  CONFIG_GPIO_TWL4030 ; 
 int /*<<< orphan*/  CONFIG_INPUT_TWL4030_PWRBUTTON ; 
 int /*<<< orphan*/  CONFIG_KEYBOARD_TWL4030 ; 
 int /*<<< orphan*/  CONFIG_MFD_TWL4030_AUDIO ; 
 int /*<<< orphan*/  CONFIG_PWM_TWL ; 
 int /*<<< orphan*/  CONFIG_PWM_TWL_LED ; 
 int /*<<< orphan*/  CONFIG_REGULATOR_TWL4030 ; 
 int /*<<< orphan*/  CONFIG_RTC_DRV_TWL4030 ; 
 int /*<<< orphan*/  CONFIG_TWL4030_MADC ; 
 int /*<<< orphan*/  CONFIG_TWL4030_POWER ; 
 int /*<<< orphan*/  CONFIG_TWL4030_USB ; 
 int /*<<< orphan*/  CONFIG_TWL4030_WATCHDOG ; 
 unsigned int GPIO_INTR_OFFSET ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct device*) ; 
 unsigned int KEYPAD_INTR_OFFSET ; 
 unsigned int MADC_INTR_OFFSET ; 
 int PTR_ERR (struct device*) ; 
 int REGULATOR_CHANGE_MODE ; 
 int REGULATOR_CHANGE_STATUS ; 
 int REGULATOR_MODE_NORMAL ; 
 int REGULATOR_MODE_STANDBY ; 
 unsigned int RTC_INTR_OFFSET ; 
 unsigned long TPS_SUBSET ; 
 int /*<<< orphan*/  TWL4030_MODULE_AUDIO_VOICE ; 
 int /*<<< orphan*/  TWL4030_MODULE_GPIO ; 
 int /*<<< orphan*/  TWL4030_MODULE_KEYPAD ; 
 int /*<<< orphan*/  TWL4030_MODULE_MADC ; 
 int /*<<< orphan*/  TWL4030_REG_VAUX1 ; 
 int /*<<< orphan*/  TWL4030_REG_VAUX2 ; 
 int /*<<< orphan*/  TWL4030_REG_VAUX2_4030 ; 
 int /*<<< orphan*/  TWL4030_REG_VAUX3 ; 
 int /*<<< orphan*/  TWL4030_REG_VAUX4 ; 
 int /*<<< orphan*/  TWL4030_REG_VDAC ; 
 int /*<<< orphan*/  TWL4030_REG_VDD1 ; 
 int /*<<< orphan*/  TWL4030_REG_VDD2 ; 
 int /*<<< orphan*/  TWL4030_REG_VINTANA1 ; 
 int /*<<< orphan*/  TWL4030_REG_VINTANA2 ; 
 int /*<<< orphan*/  TWL4030_REG_VINTDIG ; 
 int /*<<< orphan*/  TWL4030_REG_VIO ; 
 int /*<<< orphan*/  TWL4030_REG_VMMC1 ; 
 int /*<<< orphan*/  TWL4030_REG_VMMC2 ; 
 int /*<<< orphan*/  TWL4030_REG_VPLL1 ; 
 int /*<<< orphan*/  TWL4030_REG_VPLL2 ; 
 int /*<<< orphan*/  TWL4030_REG_VSIM ; 
 int /*<<< orphan*/  TWL4030_REG_VUSB1V5 ; 
 int /*<<< orphan*/  TWL4030_REG_VUSB1V8 ; 
 int /*<<< orphan*/  TWL4030_REG_VUSB3V1 ; 
 unsigned long TWL4030_VAUX2 ; 
 unsigned long TWL5031 ; 
 int /*<<< orphan*/  TWL_MODULE_LED ; 
 int /*<<< orphan*/  TWL_MODULE_MAIN_CHARGE ; 
 int /*<<< orphan*/  TWL_MODULE_PM_MASTER ; 
 int /*<<< orphan*/  TWL_MODULE_PM_RECEIVER ; 
 int /*<<< orphan*/  TWL_MODULE_PWM ; 
 int /*<<< orphan*/  TWL_MODULE_RTC ; 
 int /*<<< orphan*/  TWL_MODULE_USB ; 
 unsigned int USB_INTR_OFFSET ; 
 unsigned int USB_PRES_INTR_OFFSET ; 
 struct device* add_child (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int,unsigned int,unsigned int) ; 
 struct device* add_regulator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 struct device* add_regulator_linked (int /*<<< orphan*/ ,struct regulator_init_data*,struct regulator_consumer_supply*,int,unsigned long) ; 
 void* dev_name (struct device*) ; 
 scalar_t__ twl_class_is_4030 () ; 

__attribute__((used)) static int
add_children(struct twl4030_platform_data *pdata, unsigned irq_base,
		unsigned long features)
{
	struct device	*child;

	if (IS_ENABLED(CONFIG_GPIO_TWL4030) && pdata->gpio) {
		child = add_child(TWL4030_MODULE_GPIO, "twl4030_gpio",
				pdata->gpio, sizeof(*pdata->gpio),
				false, irq_base + GPIO_INTR_OFFSET, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (IS_ENABLED(CONFIG_KEYBOARD_TWL4030) && pdata->keypad) {
		child = add_child(TWL4030_MODULE_KEYPAD, "twl4030_keypad",
				pdata->keypad, sizeof(*pdata->keypad),
				true, irq_base + KEYPAD_INTR_OFFSET, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (IS_ENABLED(CONFIG_TWL4030_MADC) && pdata->madc &&
	    twl_class_is_4030()) {
		child = add_child(TWL4030_MODULE_MADC, "twl4030_madc",
				pdata->madc, sizeof(*pdata->madc),
				true, irq_base + MADC_INTR_OFFSET, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (IS_ENABLED(CONFIG_RTC_DRV_TWL4030)) {
		/*
		 * REVISIT platform_data here currently might expose the
		 * "msecure" line ... but for now we just expect board
		 * setup to tell the chip "it's always ok to SET_TIME".
		 * Eventually, Linux might become more aware of such
		 * HW security concerns, and "least privilege".
		 */
		child = add_child(TWL_MODULE_RTC, "twl_rtc", NULL, 0,
				true, irq_base + RTC_INTR_OFFSET, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (IS_ENABLED(CONFIG_PWM_TWL)) {
		child = add_child(TWL_MODULE_PWM, "twl-pwm", NULL, 0,
				  false, 0, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (IS_ENABLED(CONFIG_PWM_TWL_LED)) {
		child = add_child(TWL_MODULE_LED, "twl-pwmled", NULL, 0,
				  false, 0, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (IS_ENABLED(CONFIG_TWL4030_USB) && pdata->usb &&
	    twl_class_is_4030()) {

		static struct regulator_consumer_supply usb1v5 = {
			.supply =	"usb1v5",
		};
		static struct regulator_consumer_supply usb1v8 = {
			.supply =	"usb1v8",
		};
		static struct regulator_consumer_supply usb3v1 = {
			.supply =	"usb3v1",
		};

	/* First add the regulators so that they can be used by transceiver */
		if (IS_ENABLED(CONFIG_REGULATOR_TWL4030)) {
			/* this is a template that gets copied */
			struct regulator_init_data usb_fixed = {
				.constraints.valid_modes_mask =
					REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_STANDBY,
				.constraints.valid_ops_mask =
					REGULATOR_CHANGE_MODE
					| REGULATOR_CHANGE_STATUS,
			};

			child = add_regulator_linked(TWL4030_REG_VUSB1V5,
						      &usb_fixed, &usb1v5, 1,
						      features);
			if (IS_ERR(child))
				return PTR_ERR(child);

			child = add_regulator_linked(TWL4030_REG_VUSB1V8,
						      &usb_fixed, &usb1v8, 1,
						      features);
			if (IS_ERR(child))
				return PTR_ERR(child);

			child = add_regulator_linked(TWL4030_REG_VUSB3V1,
						      &usb_fixed, &usb3v1, 1,
						      features);
			if (IS_ERR(child))
				return PTR_ERR(child);

		}

		child = add_child(TWL_MODULE_USB, "twl4030_usb",
				pdata->usb, sizeof(*pdata->usb), true,
				/* irq0 = USB_PRES, irq1 = USB */
				irq_base + USB_PRES_INTR_OFFSET,
				irq_base + USB_INTR_OFFSET);

		if (IS_ERR(child))
			return PTR_ERR(child);

		/* we need to connect regulators to this transceiver */
		if (IS_ENABLED(CONFIG_REGULATOR_TWL4030) && child) {
			usb1v5.dev_name = dev_name(child);
			usb1v8.dev_name = dev_name(child);
			usb3v1.dev_name = dev_name(child);
		}
	}

	if (IS_ENABLED(CONFIG_TWL4030_WATCHDOG) && twl_class_is_4030()) {
		child = add_child(TWL_MODULE_PM_RECEIVER, "twl4030_wdt", NULL,
				  0, false, 0, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (IS_ENABLED(CONFIG_INPUT_TWL4030_PWRBUTTON) && twl_class_is_4030()) {
		child = add_child(TWL_MODULE_PM_MASTER, "twl4030_pwrbutton",
				  NULL, 0, true, irq_base + 8 + 0, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (IS_ENABLED(CONFIG_MFD_TWL4030_AUDIO) && pdata->audio &&
	    twl_class_is_4030()) {
		child = add_child(TWL4030_MODULE_AUDIO_VOICE, "twl4030-audio",
				pdata->audio, sizeof(*pdata->audio),
				false, 0, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	/* twl4030 regulators */
	if (IS_ENABLED(CONFIG_REGULATOR_TWL4030) && twl_class_is_4030()) {
		child = add_regulator(TWL4030_REG_VPLL1, pdata->vpll1,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VIO, pdata->vio,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VDD1, pdata->vdd1,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VDD2, pdata->vdd2,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VMMC1, pdata->vmmc1,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VDAC, pdata->vdac,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator((features & TWL4030_VAUX2)
					? TWL4030_REG_VAUX2_4030
					: TWL4030_REG_VAUX2,
				pdata->vaux2, features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VINTANA1, pdata->vintana1,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VINTANA2, pdata->vintana2,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VINTDIG, pdata->vintdig,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	/* maybe add LDOs that are omitted on cost-reduced parts */
	if (IS_ENABLED(CONFIG_REGULATOR_TWL4030) && !(features & TPS_SUBSET)
	  && twl_class_is_4030()) {
		child = add_regulator(TWL4030_REG_VPLL2, pdata->vpll2,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VMMC2, pdata->vmmc2,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VSIM, pdata->vsim,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VAUX1, pdata->vaux1,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VAUX3, pdata->vaux3,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VAUX4, pdata->vaux4,
					features);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (IS_ENABLED(CONFIG_CHARGER_TWL4030) && pdata->bci &&
			!(features & (TPS_SUBSET | TWL5031))) {
		child = add_child(TWL_MODULE_MAIN_CHARGE, "twl4030_bci",
				pdata->bci, sizeof(*pdata->bci), false,
				/* irq0 = CHG_PRES, irq1 = BCI */
				irq_base + BCI_PRES_INTR_OFFSET,
				irq_base + BCI_INTR_OFFSET);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (IS_ENABLED(CONFIG_TWL4030_POWER) && pdata->power) {
		child = add_child(TWL_MODULE_PM_MASTER, "twl4030_power",
				  pdata->power, sizeof(*pdata->power), false,
				  0, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	return 0;
}