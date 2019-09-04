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
typedef  int /*<<< orphan*/  u8 ;
struct wbsd_host {int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WBSD_IDX_SETUP ; 
 int /*<<< orphan*/  WBSD_SOFT_RESET ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbsd_read_index (struct wbsd_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbsd_write_index (struct wbsd_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wbsd_reset(struct wbsd_host *host)
{
	u8 setup;

	pr_err("%s: Resetting chip\n", mmc_hostname(host->mmc));

	/*
	 * Soft reset of chip (SD/MMC part).
	 */
	setup = wbsd_read_index(host, WBSD_IDX_SETUP);
	setup |= WBSD_SOFT_RESET;
	wbsd_write_index(host, WBSD_IDX_SETUP, setup);
}