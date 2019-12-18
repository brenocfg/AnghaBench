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
struct spi_device {int dummy; } ;
struct device {int dummy; } ;
struct applespi_data {int /*<<< orphan*/  have_bl_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  applespi_save_bl_level (struct applespi_data*,int /*<<< orphan*/ ) ; 
 struct applespi_data* spi_get_drvdata (struct spi_device*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int applespi_poweroff_late(struct device *dev)
{
	struct spi_device *spi = to_spi_device(dev);
	struct applespi_data *applespi = spi_get_drvdata(spi);

	applespi_save_bl_level(applespi, applespi->have_bl_level);

	return 0;
}