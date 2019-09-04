#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mmci_host {int datactrl_reg; scalar_t__ base; TYPE_1__* variant; } ;
struct TYPE_2__ {int busy_dpsm_flag; } ;

/* Variables and functions */
 scalar_t__ MMCIDATACTRL ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mmci_write_datactrlreg(struct mmci_host *host, u32 datactrl)
{
	/* Keep busy mode in DPSM if enabled */
	datactrl |= host->datactrl_reg & host->variant->busy_dpsm_flag;

	if (host->datactrl_reg != datactrl) {
		host->datactrl_reg = datactrl;
		writel(datactrl, host->base + MMCIDATACTRL);
	}
}