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
 int /*<<< orphan*/  DEVICE_SD ; 
 int /*<<< orphan*/  WBSD_CONF_DEVICE ; 
 int /*<<< orphan*/  WBSD_CONF_DRQ ; 
 int /*<<< orphan*/  WBSD_CONF_IRQ ; 
 int /*<<< orphan*/  WBSD_CONF_PORT_HI ; 
 int /*<<< orphan*/  WBSD_CONF_PORT_LO ; 
 int /*<<< orphan*/  wbsd_lock_config (struct wbsd_host*) ; 
 int wbsd_read_config (struct wbsd_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbsd_unlock_config (struct wbsd_host*) ; 
 int /*<<< orphan*/  wbsd_write_config (struct wbsd_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wbsd_chip_validate(struct wbsd_host *host)
{
	int base, irq, dma;

	wbsd_unlock_config(host);

	/*
	 * Select SD/MMC function.
	 */
	wbsd_write_config(host, WBSD_CONF_DEVICE, DEVICE_SD);

	/*
	 * Read configuration.
	 */
	base = wbsd_read_config(host, WBSD_CONF_PORT_HI) << 8;
	base |= wbsd_read_config(host, WBSD_CONF_PORT_LO);

	irq = wbsd_read_config(host, WBSD_CONF_IRQ);

	dma = wbsd_read_config(host, WBSD_CONF_DRQ);

	wbsd_lock_config(host);

	/*
	 * Validate against given configuration.
	 */
	if (base != host->base)
		return 0;
	if (irq != host->irq)
		return 0;
	if ((dma != host->dma) && (host->dma != -1))
		return 0;

	return 1;
}