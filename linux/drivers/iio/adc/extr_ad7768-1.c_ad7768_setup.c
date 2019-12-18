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
struct ad7768_state {int /*<<< orphan*/  gpio_sync_in; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7768_REG_SYNC_RESET ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int ad7768_set_freq (struct ad7768_state*,int) ; 
 int ad7768_spi_reg_write (struct ad7768_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7768_setup(struct ad7768_state *st)
{
	int ret;

	/*
	 * Two writes to the SPI_RESET[1:0] bits are required to initiate
	 * a software reset. The bits must first be set to 11, and then
	 * to 10. When the sequence is detected, the reset occurs.
	 * See the datasheet, page 70.
	 */
	ret = ad7768_spi_reg_write(st, AD7768_REG_SYNC_RESET, 0x3);
	if (ret)
		return ret;

	ret = ad7768_spi_reg_write(st, AD7768_REG_SYNC_RESET, 0x2);
	if (ret)
		return ret;

	st->gpio_sync_in = devm_gpiod_get(&st->spi->dev, "adi,sync-in",
					  GPIOD_OUT_LOW);
	if (IS_ERR(st->gpio_sync_in))
		return PTR_ERR(st->gpio_sync_in);

	/* Set the default sampling frequency to 32000 kSPS */
	return ad7768_set_freq(st, 32000);
}