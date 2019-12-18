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
struct tosa_lcd_data {struct spi_device* spi; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TG_PINICTL ; 
 int /*<<< orphan*/  TOSA_GPIO_TG_ON ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  tosa_tg_send (struct spi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tosa_lcd_tg_off(struct tosa_lcd_data *data)
{
	struct spi_device *spi = data->spi;

	/* TG LCD VHSA off */
	tosa_tg_send(spi, TG_PINICTL, 0x4);
	mdelay(50);

	/* TG LCD signal off */
	tosa_tg_send(spi, TG_PINICTL, 0x6);
	mdelay(50);

	/* TG Off */
	gpio_set_value(TOSA_GPIO_TG_ON, 1);
	mdelay(100);
}