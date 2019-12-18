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
typedef  int /*<<< orphan*/  u8 ;
struct sdio_func {TYPE_2__* card; } ;
struct TYPE_3__ {scalar_t__ bus_width; } ;
struct mmc_host {int caps; TYPE_1__ ios; } ;
struct if_sdio_card {scalar_t__ model; int ioport; struct sdio_func* func; } ;
struct TYPE_4__ {int /*<<< orphan*/  quirks; struct mmc_host* host; } ;

/* Variables and functions */
 scalar_t__ IF_SDIO_IOPORT ; 
 scalar_t__ MMC_BUS_WIDTH_1 ; 
 int MMC_CAP_SDIO_IRQ ; 
 int /*<<< orphan*/  MMC_QUIRK_LENIENT_FN0 ; 
 scalar_t__ MODEL_8686 ; 
 int /*<<< orphan*/  SDIO_BUS_ECSI ; 
 int /*<<< orphan*/  SDIO_CCCR_IF ; 
 int if_sdio_prog_firmware (struct if_sdio_card*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 int sdio_enable_func (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_f0_readb (struct sdio_func*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdio_f0_writeb (struct sdio_func*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sdio_readb (struct sdio_func*,scalar_t__,int*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 

__attribute__((used)) static int if_sdio_power_on(struct if_sdio_card *card)
{
	struct sdio_func *func = card->func;
	struct mmc_host *host = func->card->host;
	int ret;

	sdio_claim_host(func);

	ret = sdio_enable_func(func);
	if (ret)
		goto release;

	/* For 1-bit transfers to the 8686 model, we need to enable the
	 * interrupt flag in the CCCR register. Set the MMC_QUIRK_LENIENT_FN0
	 * bit to allow access to non-vendor registers. */
	if ((card->model == MODEL_8686) &&
	    (host->caps & MMC_CAP_SDIO_IRQ) &&
	    (host->ios.bus_width == MMC_BUS_WIDTH_1)) {
		u8 reg;

		func->card->quirks |= MMC_QUIRK_LENIENT_FN0;
		reg = sdio_f0_readb(func, SDIO_CCCR_IF, &ret);
		if (ret)
			goto disable;

		reg |= SDIO_BUS_ECSI;
		sdio_f0_writeb(func, reg, SDIO_CCCR_IF, &ret);
		if (ret)
			goto disable;
	}

	card->ioport = sdio_readb(func, IF_SDIO_IOPORT, &ret);
	if (ret)
		goto disable;

	card->ioport |= sdio_readb(func, IF_SDIO_IOPORT + 1, &ret) << 8;
	if (ret)
		goto disable;

	card->ioport |= sdio_readb(func, IF_SDIO_IOPORT + 2, &ret) << 16;
	if (ret)
		goto disable;

	sdio_release_host(func);
	ret = if_sdio_prog_firmware(card);
	if (ret) {
		sdio_claim_host(func);
		goto disable;
	}

	return 0;

disable:
	sdio_disable_func(func);
release:
	sdio_release_host(func);
	return ret;
}