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
struct tosa_lcd_data {int /*<<< orphan*/  i2c; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 struct tosa_lcd_data* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  tosa_lcd_tg_off (struct tosa_lcd_data*) ; 

__attribute__((used)) static int tosa_lcd_remove(struct spi_device *spi)
{
	struct tosa_lcd_data *data = spi_get_drvdata(spi);

	i2c_unregister_device(data->i2c);

	tosa_lcd_tg_off(data);

	return 0;
}