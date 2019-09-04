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
typedef  int u16 ;
struct mmc_request {TYPE_2__* data; } ;
struct mmc_omap_host {TYPE_1__* current_slot; } ;
struct TYPE_4__ {unsigned int timeout_ns; scalar_t__ timeout_clks; } ;
struct TYPE_3__ {int fclk_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTO ; 
 int OMAP_MMC_READ (struct mmc_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_MMC_WRITE (struct mmc_omap_host*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SDIO ; 

__attribute__((used)) static inline void set_data_timeout(struct mmc_omap_host *host, struct mmc_request *req)
{
	unsigned int timeout, cycle_ns;
	u16 reg;

	cycle_ns = 1000000000 / host->current_slot->fclk_freq;
	timeout = req->data->timeout_ns / cycle_ns;
	timeout += req->data->timeout_clks;

	/* Check if we need to use timeout multiplier register */
	reg = OMAP_MMC_READ(host, SDIO);
	if (timeout > 0xffff) {
		reg |= (1 << 5);
		timeout /= 1024;
	} else
		reg &= ~(1 << 5);
	OMAP_MMC_WRITE(host, SDIO, reg);
	OMAP_MMC_WRITE(host, DTO, timeout);
}