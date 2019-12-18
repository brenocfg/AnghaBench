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
typedef  int /*<<< orphan*/  u16 ;
struct sdhci_host {scalar_t__ version; int flags; scalar_t__ v4_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_CTRL_64BIT_ADDR ; 
 int /*<<< orphan*/  SDHCI_CTRL_ADMA32 ; 
 int /*<<< orphan*/  SDHCI_CTRL_ADMA64 ; 
 int /*<<< orphan*/  SDHCI_CTRL_DMA_MASK ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int SDHCI_REQ_USE_DMA ; 
 scalar_t__ SDHCI_SPEC_200 ; 
 int SDHCI_USE_64_BIT_DMA ; 
 int SDHCI_USE_ADMA ; 
 int /*<<< orphan*/  sdhci_readb (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_config_dma(struct sdhci_host *host)
{
	u8 ctrl;
	u16 ctrl2;

	if (host->version < SDHCI_SPEC_200)
		return;

	ctrl = sdhci_readb(host, SDHCI_HOST_CONTROL);

	/*
	 * Always adjust the DMA selection as some controllers
	 * (e.g. JMicron) can't do PIO properly when the selection
	 * is ADMA.
	 */
	ctrl &= ~SDHCI_CTRL_DMA_MASK;
	if (!(host->flags & SDHCI_REQ_USE_DMA))
		goto out;

	/* Note if DMA Select is zero then SDMA is selected */
	if (host->flags & SDHCI_USE_ADMA)
		ctrl |= SDHCI_CTRL_ADMA32;

	if (host->flags & SDHCI_USE_64_BIT_DMA) {
		/*
		 * If v4 mode, all supported DMA can be 64-bit addressing if
		 * controller supports 64-bit system address, otherwise only
		 * ADMA can support 64-bit addressing.
		 */
		if (host->v4_mode) {
			ctrl2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
			ctrl2 |= SDHCI_CTRL_64BIT_ADDR;
			sdhci_writew(host, ctrl2, SDHCI_HOST_CONTROL2);
		} else if (host->flags & SDHCI_USE_ADMA) {
			/*
			 * Don't need to undo SDHCI_CTRL_ADMA32 in order to
			 * set SDHCI_CTRL_ADMA64.
			 */
			ctrl |= SDHCI_CTRL_ADMA64;
		}
	}

out:
	sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);
}