#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  wide_bus; scalar_t__ low_speed; } ;
struct mmc_card {TYPE_2__* host; TYPE_1__ cccr; } ;
struct TYPE_4__ {int caps; } ;

/* Variables and functions */
 int MMC_CAP_4_BIT_DATA ; 
 int SDIO_BUS_WIDTH_4BIT ; 
 int SDIO_BUS_WIDTH_MASK ; 
 int SDIO_BUS_WIDTH_RESERVED ; 
 int /*<<< orphan*/  SDIO_CCCR_IF ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_2__*) ; 
 int mmc_io_rw_direct (struct mmc_card*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sdio_enable_wide(struct mmc_card *card)
{
	int ret;
	u8 ctrl;

	if (!(card->host->caps & MMC_CAP_4_BIT_DATA))
		return 0;

	if (card->cccr.low_speed && !card->cccr.wide_bus)
		return 0;

	ret = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_IF, 0, &ctrl);
	if (ret)
		return ret;

	if ((ctrl & SDIO_BUS_WIDTH_MASK) == SDIO_BUS_WIDTH_RESERVED)
		pr_warn("%s: SDIO_CCCR_IF is invalid: 0x%02x\n",
			mmc_hostname(card->host), ctrl);

	/* set as 4-bit bus width */
	ctrl &= ~SDIO_BUS_WIDTH_MASK;
	ctrl |= SDIO_BUS_WIDTH_4BIT;

	ret = mmc_io_rw_direct(card, 1, 0, SDIO_CCCR_IF, ctrl, NULL);
	if (ret)
		return ret;

	return 1;
}