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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_ALL_SEND_CID ; 
 scalar_t__ mmc_host_is_spi (struct mmc_host*) ; 
 int mmc_send_cxd_native (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mmc_spi_send_cid (struct mmc_host*,int /*<<< orphan*/ *) ; 

int mmc_send_cid(struct mmc_host *host, u32 *cid)
{
	if (mmc_host_is_spi(host))
		return mmc_spi_send_cid(host, cid);

	return mmc_send_cxd_native(host, 0, cid, MMC_ALL_SEND_CID);
}