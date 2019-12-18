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
struct TYPE_3__ {int /*<<< orphan*/  po; int /*<<< orphan*/  reset; } ;
struct ifx_spi_device {scalar_t__ mdm_reset_state; TYPE_2__* spi_dev; int /*<<< orphan*/  mdm_reset_wait; TYPE_1__ gpio; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFX_RESET_TIMEOUT ; 
 int /*<<< orphan*/  MR_COMPLETE ; 
 int /*<<< orphan*/  MR_START ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ifx_spi_reset(struct ifx_spi_device *ifx_dev)
{
	int ret;
	/*
	 * set up modem power, reset
	 *
	 * delays are required on some platforms for the modem
	 * to reset properly
	 */
	set_bit(MR_START, &ifx_dev->mdm_reset_state);
	gpio_set_value(ifx_dev->gpio.po, 0);
	gpio_set_value(ifx_dev->gpio.reset, 0);
	msleep(25);
	gpio_set_value(ifx_dev->gpio.reset, 1);
	msleep(1);
	gpio_set_value(ifx_dev->gpio.po, 1);
	msleep(1);
	gpio_set_value(ifx_dev->gpio.po, 0);
	ret = wait_event_timeout(ifx_dev->mdm_reset_wait,
				 test_bit(MR_COMPLETE,
					  &ifx_dev->mdm_reset_state),
				 IFX_RESET_TIMEOUT);
	if (!ret)
		dev_warn(&ifx_dev->spi_dev->dev, "Modem reset timeout: (state:%lx)",
			 ifx_dev->mdm_reset_state);

	ifx_dev->mdm_reset_state = 0;
	return ret;
}