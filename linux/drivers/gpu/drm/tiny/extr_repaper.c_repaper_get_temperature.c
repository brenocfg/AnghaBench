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
struct repaper_epd {unsigned int factored_stage_time; unsigned int stage_time; TYPE_1__* spi; int /*<<< orphan*/  thermal; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*,int) ; 
 int thermal_zone_get_temp (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void repaper_get_temperature(struct repaper_epd *epd)
{
	int ret, temperature = 0;
	unsigned int factor10x;

	if (!epd->thermal)
		return;

	ret = thermal_zone_get_temp(epd->thermal, &temperature);
	if (ret) {
		DRM_DEV_ERROR(&epd->spi->dev, "Failed to get temperature (%d)\n", ret);
		return;
	}

	temperature /= 1000;

	if (temperature <= -10)
		factor10x = 170;
	else if (temperature <= -5)
		factor10x = 120;
	else if (temperature <= 5)
		factor10x = 80;
	else if (temperature <= 10)
		factor10x = 40;
	else if (temperature <= 15)
		factor10x = 30;
	else if (temperature <= 20)
		factor10x = 20;
	else if (temperature <= 40)
		factor10x = 10;
	else
		factor10x = 7;

	epd->factored_stage_time = epd->stage_time * factor10x / 10;
}