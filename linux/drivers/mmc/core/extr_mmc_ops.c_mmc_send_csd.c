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
struct mmc_card {int rca; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_SEND_CSD ; 
 scalar_t__ mmc_host_is_spi (int /*<<< orphan*/ ) ; 
 int mmc_send_cxd_native (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mmc_spi_send_csd (struct mmc_card*,int /*<<< orphan*/ *) ; 

int mmc_send_csd(struct mmc_card *card, u32 *csd)
{
	if (mmc_host_is_spi(card->host))
		return mmc_spi_send_csd(card, csd);

	return mmc_send_cxd_native(card->host, card->rca << 16,	csd,
				MMC_SEND_CSD);
}