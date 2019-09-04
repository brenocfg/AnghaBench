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
struct wbsd_host {int base; int irq; int dma; } ;

/* Variables and functions */
 int DEVICE_SD ; 
 int /*<<< orphan*/  WBSD_CONF_DEVICE ; 
 int /*<<< orphan*/  WBSD_CONF_DRQ ; 
 int /*<<< orphan*/  WBSD_CONF_ENABLE ; 
 int /*<<< orphan*/  WBSD_CONF_IRQ ; 
 int /*<<< orphan*/  WBSD_CONF_PINS ; 
 int /*<<< orphan*/  WBSD_CONF_PORT_HI ; 
 int /*<<< orphan*/  WBSD_CONF_PORT_LO ; 
 int /*<<< orphan*/  WBSD_CONF_POWER ; 
 int /*<<< orphan*/  WBSD_CONF_SWRST ; 
 int WBSD_PINS_DETECT_GP11 ; 
 int /*<<< orphan*/  wbsd_lock_config (struct wbsd_host*) ; 
 int /*<<< orphan*/  wbsd_unlock_config (struct wbsd_host*) ; 
 int /*<<< orphan*/  wbsd_write_config (struct wbsd_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wbsd_chip_config(struct wbsd_host *host)
{
	wbsd_unlock_config(host);

	/*
	 * Reset the chip.
	 */
	wbsd_write_config(host, WBSD_CONF_SWRST, 1);
	wbsd_write_config(host, WBSD_CONF_SWRST, 0);

	/*
	 * Select SD/MMC function.
	 */
	wbsd_write_config(host, WBSD_CONF_DEVICE, DEVICE_SD);

	/*
	 * Set up card detection.
	 */
	wbsd_write_config(host, WBSD_CONF_PINS, WBSD_PINS_DETECT_GP11);

	/*
	 * Configure chip
	 */
	wbsd_write_config(host, WBSD_CONF_PORT_HI, host->base >> 8);
	wbsd_write_config(host, WBSD_CONF_PORT_LO, host->base & 0xff);

	wbsd_write_config(host, WBSD_CONF_IRQ, host->irq);

	if (host->dma >= 0)
		wbsd_write_config(host, WBSD_CONF_DRQ, host->dma);

	/*
	 * Enable and power up chip.
	 */
	wbsd_write_config(host, WBSD_CONF_ENABLE, 1);
	wbsd_write_config(host, WBSD_CONF_POWER, 0x20);

	wbsd_lock_config(host);
}