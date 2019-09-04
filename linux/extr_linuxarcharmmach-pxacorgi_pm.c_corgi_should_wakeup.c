#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  charge_mode; TYPE_1__* machinfo; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* charge ) (int /*<<< orphan*/ ) ;scalar_t__ (* read_devdata ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHRG_OFF ; 
 int /*<<< orphan*/  CORGI_GPIO_AC_IN ; 
 int /*<<< orphan*/  CORGI_GPIO_CHRG_FULL ; 
 int /*<<< orphan*/  CORGI_GPIO_KEY_INT ; 
 int /*<<< orphan*/  CORGI_GPIO_WAKEUP ; 
 int GPIO_bit (int /*<<< orphan*/ ) ; 
 int PEDR ; 
 int PWER_RTC ; 
 int /*<<< orphan*/  SHARPSL_DO_OFFLINE_CHRG ; 
 int /*<<< orphan*/  SHARPSL_LED_OFF ; 
 int /*<<< orphan*/  SHARPSL_STATUS_ACIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 TYPE_2__ sharpsl_pm ; 
 int /*<<< orphan*/  sharpsl_pm_led (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int corgi_should_wakeup(unsigned int resume_on_alarm)
{
	int is_resume = 0;

	dev_dbg(sharpsl_pm.dev, "PEDR = %x, GPIO_AC_IN = %d, "
		"GPIO_CHRG_FULL = %d, GPIO_KEY_INT = %d, GPIO_WAKEUP = %d\n",
		PEDR, gpio_get_value(CORGI_GPIO_AC_IN),
		gpio_get_value(CORGI_GPIO_CHRG_FULL),
		gpio_get_value(CORGI_GPIO_KEY_INT),
		gpio_get_value(CORGI_GPIO_WAKEUP));

	if ((PEDR & GPIO_bit(CORGI_GPIO_AC_IN))) {
		if (sharpsl_pm.machinfo->read_devdata(SHARPSL_STATUS_ACIN)) {
			/* charge on */
			dev_dbg(sharpsl_pm.dev, "ac insert\n");
			sharpsl_pm.flags |= SHARPSL_DO_OFFLINE_CHRG;
		} else {
			/* charge off */
			dev_dbg(sharpsl_pm.dev, "ac remove\n");
			sharpsl_pm_led(SHARPSL_LED_OFF);
			sharpsl_pm.machinfo->charge(0);
			sharpsl_pm.charge_mode = CHRG_OFF;
		}
	}

	if ((PEDR & GPIO_bit(CORGI_GPIO_CHRG_FULL)))
		dev_dbg(sharpsl_pm.dev, "Charge full interrupt\n");

	if (PEDR & GPIO_bit(CORGI_GPIO_KEY_INT))
		is_resume |= GPIO_bit(CORGI_GPIO_KEY_INT);

	if (PEDR & GPIO_bit(CORGI_GPIO_WAKEUP))
		is_resume |= GPIO_bit(CORGI_GPIO_WAKEUP);

	if (resume_on_alarm && (PEDR & PWER_RTC))
		is_resume |= PWER_RTC;

	dev_dbg(sharpsl_pm.dev, "is_resume: %x\n",is_resume);
	return is_resume;
}