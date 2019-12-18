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
struct ili9322 {int /*<<< orphan*/  panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ili9322_power_off (struct ili9322*) ; 
 struct ili9322* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int ili9322_remove(struct spi_device *spi)
{
	struct ili9322 *ili = spi_get_drvdata(spi);

	ili9322_power_off(ili);
	drm_panel_remove(&ili->panel);

	return 0;
}