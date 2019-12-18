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
typedef  int u32 ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int EBADMSG ; 
 int R1_SPI_ILLEGAL_COMMAND ; 
 scalar_t__ R1_STATUS (int) ; 
 int R1_SWITCH_ERROR ; 
 scalar_t__ mmc_host_is_spi (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mmc_switch_status_error(struct mmc_host *host, u32 status)
{
	if (mmc_host_is_spi(host)) {
		if (status & R1_SPI_ILLEGAL_COMMAND)
			return -EBADMSG;
	} else {
		if (R1_STATUS(status))
			pr_warn("%s: unexpected status %#x after switch\n",
				mmc_hostname(host), status);
		if (status & R1_SWITCH_ERROR)
			return -EBADMSG;
	}
	return 0;
}