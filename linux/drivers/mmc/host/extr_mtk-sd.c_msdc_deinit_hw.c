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
struct msdc_host {scalar_t__ base; scalar_t__ internal_cd; } ;

/* Variables and functions */
 scalar_t__ MSDC_INT ; 
 scalar_t__ MSDC_INTEN ; 
 scalar_t__ MSDC_PS ; 
 int /*<<< orphan*/  MSDC_PS_CDEN ; 
 scalar_t__ SDC_CFG ; 
 int /*<<< orphan*/  SDC_CFG_INSWKUP ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  sdr_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void msdc_deinit_hw(struct msdc_host *host)
{
	u32 val;

	if (host->internal_cd) {
		/* Disabled card-detect */
		sdr_clr_bits(host->base + MSDC_PS, MSDC_PS_CDEN);
		sdr_clr_bits(host->base + SDC_CFG, SDC_CFG_INSWKUP);
	}

	/* Disable and clear all interrupts */
	writel(0, host->base + MSDC_INTEN);

	val = readl(host->base + MSDC_INT);
	writel(val, host->base + MSDC_INT);
}