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
struct TYPE_2__ {int /*<<< orphan*/ * dev; } ;
struct sa1100_port {TYPE_1__ port; int /*<<< orphan*/ * gpios; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * mctrl_gpio_init_noauto (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sa1100_port*) ; 
 int /*<<< orphan*/  sa1100_reg ; 
 int uart_add_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int sa1100_serial_add_one_port(struct sa1100_port *sport, struct platform_device *dev)
{
	sport->port.dev = &dev->dev;

	// mctrl_gpio_init() requires that the GPIO driver supports interrupts,
	// but we need to support GPIO drivers for hardware that has no such
	// interrupts.  Use mctrl_gpio_init_noauto() instead.
	sport->gpios = mctrl_gpio_init_noauto(sport->port.dev, 0);
	if (IS_ERR(sport->gpios)) {
		int err = PTR_ERR(sport->gpios);

		dev_err(sport->port.dev, "failed to get mctrl gpios: %d\n",
			err);

		if (err == -EPROBE_DEFER)
			return err;

		sport->gpios = NULL;
	}

	platform_set_drvdata(dev, sport);

	return uart_add_one_port(&sa1100_reg, &sport->port);
}