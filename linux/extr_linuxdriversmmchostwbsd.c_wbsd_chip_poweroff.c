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
struct wbsd_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_SD ; 
 int /*<<< orphan*/  WBSD_CONF_DEVICE ; 
 int /*<<< orphan*/  WBSD_CONF_ENABLE ; 
 int /*<<< orphan*/  wbsd_lock_config (struct wbsd_host*) ; 
 int /*<<< orphan*/  wbsd_unlock_config (struct wbsd_host*) ; 
 int /*<<< orphan*/  wbsd_write_config (struct wbsd_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wbsd_chip_poweroff(struct wbsd_host *host)
{
	wbsd_unlock_config(host);

	wbsd_write_config(host, WBSD_CONF_DEVICE, DEVICE_SD);
	wbsd_write_config(host, WBSD_CONF_ENABLE, 0);

	wbsd_lock_config(host);
}