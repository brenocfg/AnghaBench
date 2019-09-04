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
struct dw_mci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMOD ; 
 int /*<<< orphan*/  SDMMC_IDMAC_SWRESET ; 
 int /*<<< orphan*/  mci_readl (struct dw_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_mci_idmac_reset(struct dw_mci *host)
{
	u32 bmod = mci_readl(host, BMOD);
	/* Software reset of DMA */
	bmod |= SDMMC_IDMAC_SWRESET;
	mci_writel(host, BMOD, bmod);
}