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
struct tmio_mmc_host {int bus_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DMA_ENABLE ; 
 int /*<<< orphan*/  DMA_ENABLE_DMASDRW ; 
 int /*<<< orphan*/  renesas_sdhi_sdbuf_width (struct tmio_mmc_host*,int) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void renesas_sdhi_enable_dma(struct tmio_mmc_host *host, bool enable)
{
	/* Iff regs are 8 byte apart, sdbuf is 64 bit. Otherwise always 32. */
	int width = (host->bus_shift == 2) ? 64 : 32;

	sd_ctrl_write16(host, CTL_DMA_ENABLE, enable ? DMA_ENABLE_DMASDRW : 0);
	renesas_sdhi_sdbuf_width(host, enable ? width : 16);
}