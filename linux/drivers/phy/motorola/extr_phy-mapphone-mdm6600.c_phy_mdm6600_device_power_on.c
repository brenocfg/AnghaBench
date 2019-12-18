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
struct phy_mdm6600 {int enabled; scalar_t__ status; int running; int /*<<< orphan*/  dev; int /*<<< orphan*/  ack; struct gpio_desc** ctrl_gpios; TYPE_1__* mode_gpios; } ;
struct gpio_desc {int dummy; } ;
struct TYPE_2__ {struct gpio_desc** desc; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  PHY_MDM6600_CMD_NO_BYPASS ; 
 int /*<<< orphan*/  PHY_MDM6600_ENABLED_DELAY_MS ; 
 size_t PHY_MDM6600_MODE0 ; 
 size_t PHY_MDM6600_MODE1 ; 
 int PHY_MDM6600_PHY_DELAY_MS ; 
 size_t PHY_MDM6600_POWER ; 
 size_t PHY_MDM6600_RESET ; 
 scalar_t__ PHY_MDM6600_STATUS_PANIC ; 
 scalar_t__ PHY_MDM6600_STATUS_SHUTDOWN_ACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct phy_mdm6600*) ; 
 int /*<<< orphan*/  gpiod_direction_input (struct gpio_desc*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (struct gpio_desc*,int) ; 
 int gpiod_to_irq (struct gpio_desc*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  phy_mdm6600_cmd (struct phy_mdm6600*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_mdm6600_wakeirq_thread ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_mdm6600_device_power_on(struct phy_mdm6600 *ddata)
{
	struct gpio_desc *mode_gpio0, *mode_gpio1, *reset_gpio, *power_gpio;
	int error = 0, wakeirq;

	mode_gpio0 = ddata->mode_gpios->desc[PHY_MDM6600_MODE0];
	mode_gpio1 = ddata->mode_gpios->desc[PHY_MDM6600_MODE1];
	reset_gpio = ddata->ctrl_gpios[PHY_MDM6600_RESET];
	power_gpio = ddata->ctrl_gpios[PHY_MDM6600_POWER];

	/*
	 * Shared GPIOs must be low for normal USB mode. After booting
	 * they are used for OOB wake signaling. These can be also used
	 * to configure USB flashing mode later on based on a module
	 * parameter.
	 */
	gpiod_set_value_cansleep(mode_gpio0, 0);
	gpiod_set_value_cansleep(mode_gpio1, 0);

	/* Request start-up mode */
	phy_mdm6600_cmd(ddata, PHY_MDM6600_CMD_NO_BYPASS);

	/* Request a reset first */
	gpiod_set_value_cansleep(reset_gpio, 0);
	msleep(100);

	/* Toggle power GPIO to request mdm6600 to start */
	gpiod_set_value_cansleep(power_gpio, 1);
	msleep(100);
	gpiod_set_value_cansleep(power_gpio, 0);

	/*
	 * Looks like the USB PHY needs between 2.2 to 4 seconds.
	 * If we try to use it before that, we will get L3 errors
	 * from omap-usb-host trying to access the PHY. See also
	 * phy_mdm6600_init() for -EPROBE_DEFER.
	 */
	msleep(PHY_MDM6600_PHY_DELAY_MS);
	ddata->enabled = true;

	/* Booting up the rest of MDM6600 will take total about 8 seconds */
	dev_info(ddata->dev, "Waiting for power up request to complete..\n");
	if (wait_for_completion_timeout(&ddata->ack,
			msecs_to_jiffies(PHY_MDM6600_ENABLED_DELAY_MS))) {
		if (ddata->status > PHY_MDM6600_STATUS_PANIC &&
		    ddata->status < PHY_MDM6600_STATUS_SHUTDOWN_ACK)
			dev_info(ddata->dev, "Powered up OK\n");
	} else {
		ddata->enabled = false;
		error = -ETIMEDOUT;
		dev_err(ddata->dev, "Timed out powering up\n");
	}

	/* Reconfigure mode1 GPIO as input for OOB wake */
	gpiod_direction_input(mode_gpio1);

	wakeirq = gpiod_to_irq(mode_gpio1);
	if (wakeirq <= 0)
		return wakeirq;

	error = devm_request_threaded_irq(ddata->dev, wakeirq, NULL,
					  phy_mdm6600_wakeirq_thread,
					  IRQF_TRIGGER_RISING |
					  IRQF_TRIGGER_FALLING |
					  IRQF_ONESHOT,
					  "mdm6600-wake",
					  ddata);
	if (error)
		dev_warn(ddata->dev, "no modem wakeirq irq%i: %i\n",
			 wakeirq, error);

	ddata->running = true;

	return error;
}