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
struct tosa_lcd_data {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  TG_GPOSR ; 
 int /*<<< orphan*/  TG_TPOSCTL ; 
 int /*<<< orphan*/  TOSA_GPIO_TG_ON ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  tosa_tg_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tosa_lcd_tg_init(struct tosa_lcd_data *data)
{
	/* TG on */
	gpio_set_value(TOSA_GPIO_TG_ON, 0);

	mdelay(60);

	/* delayed 0clk TCTL signal for VGA */
	tosa_tg_send(data->spi, TG_TPOSCTL, 0x00);
	/* GPOS0=powercontrol, GPOS1=GPIO, GPOS2=TCTL */
	tosa_tg_send(data->spi, TG_GPOSR, 0x02);
}