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
typedef  int u8 ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDIO_CCCR_ABORT ; 
 int mmc_io_rw_direct_host (struct mmc_host*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

int sdio_reset(struct mmc_host *host)
{
	int ret;
	u8 abort;

	/* SDIO Simplified Specification V2.0, 4.4 Reset for SDIO */

	ret = mmc_io_rw_direct_host(host, 0, 0, SDIO_CCCR_ABORT, 0, &abort);
	if (ret)
		abort = 0x08;
	else
		abort |= 0x08;

	return mmc_io_rw_direct_host(host, 1, 0, SDIO_CCCR_ABORT, abort, NULL);
}