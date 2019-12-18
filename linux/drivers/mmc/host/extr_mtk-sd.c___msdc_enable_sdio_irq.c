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
struct msdc_host {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MSDC_INTEN ; 
 int /*<<< orphan*/  MSDC_INTEN_SDIOIRQ ; 
 scalar_t__ SDC_CFG ; 
 int /*<<< orphan*/  SDC_CFG_SDIOIDE ; 
 int /*<<< orphan*/  sdr_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdr_set_bits (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __msdc_enable_sdio_irq(struct msdc_host *host, int enb)
{
	if (enb) {
		sdr_set_bits(host->base + MSDC_INTEN, MSDC_INTEN_SDIOIRQ);
		sdr_set_bits(host->base + SDC_CFG, SDC_CFG_SDIOIDE);
	} else {
		sdr_clr_bits(host->base + MSDC_INTEN, MSDC_INTEN_SDIOIRQ);
		sdr_clr_bits(host->base + SDC_CFG, SDC_CFG_SDIOIDE);
	}
}