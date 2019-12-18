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
struct repaper_epd {scalar_t__ discharge; int /*<<< orphan*/  spi; scalar_t__ border; scalar_t__ panel_on; scalar_t__ reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  repaper_spi_mosi_low (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void power_off(struct repaper_epd *epd)
{
	/* Turn off power and all signals */
	gpiod_set_value_cansleep(epd->reset, 0);
	gpiod_set_value_cansleep(epd->panel_on, 0);
	if (epd->border)
		gpiod_set_value_cansleep(epd->border, 0);

	/* Ensure SPI MOSI and CLOCK are Low before CS Low */
	repaper_spi_mosi_low(epd->spi);

	/* Discharge pulse */
	gpiod_set_value_cansleep(epd->discharge, 1);
	msleep(150);
	gpiod_set_value_cansleep(epd->discharge, 0);
}