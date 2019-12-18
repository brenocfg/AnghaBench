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
struct TYPE_2__ {int /*<<< orphan*/  srdy; } ;
struct ifx_spi_device {int /*<<< orphan*/  spi_timer; int /*<<< orphan*/  flags; TYPE_1__ gpio; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IFX_SPI_POWER_DATA_PENDING ; 
 int /*<<< orphan*/  IFX_SPI_STATE_TIMER_PENDING ; 
 int IFX_SPI_TIMEOUT_SEC ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifx_spi_power_state_set (struct ifx_spi_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mrdy_set_high (struct ifx_spi_device*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mrdy_assert(struct ifx_spi_device *ifx_dev)
{
	int val = gpio_get_value(ifx_dev->gpio.srdy);
	if (!val) {
		if (!test_and_set_bit(IFX_SPI_STATE_TIMER_PENDING,
				      &ifx_dev->flags)) {
			mod_timer(&ifx_dev->spi_timer,jiffies + IFX_SPI_TIMEOUT_SEC*HZ);

		}
	}
	ifx_spi_power_state_set(ifx_dev, IFX_SPI_POWER_DATA_PENDING);
	mrdy_set_high(ifx_dev);
}