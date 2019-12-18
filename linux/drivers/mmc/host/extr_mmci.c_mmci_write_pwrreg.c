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
typedef  scalar_t__ u32 ;
struct mmci_host {scalar_t__ pwr_reg; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MMCIPOWER ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

void mmci_write_pwrreg(struct mmci_host *host, u32 pwr)
{
	if (host->pwr_reg != pwr) {
		host->pwr_reg = pwr;
		writel(pwr, host->base + MMCIPOWER);
	}
}