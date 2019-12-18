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
typedef  int u32 ;
struct msdc_host {int timeout_ns; int timeout_clks; scalar_t__ base; TYPE_2__* dev_comp; TYPE_1__* mmc; } ;
struct TYPE_4__ {int clk_div_bits; } ;
struct TYPE_3__ {unsigned long actual_clock; } ;

/* Variables and functions */
 scalar_t__ MSDC_CFG ; 
 int /*<<< orphan*/  MSDC_CFG_CKMOD ; 
 int /*<<< orphan*/  MSDC_CFG_CKMOD_EXTRA ; 
 scalar_t__ SDC_CFG ; 
 int /*<<< orphan*/  SDC_CFG_DTOC ; 
 int /*<<< orphan*/  sdr_get_field (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdr_set_field (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void msdc_set_timeout(struct msdc_host *host, u32 ns, u32 clks)
{
	u32 timeout, clk_ns;
	u32 mode = 0;

	host->timeout_ns = ns;
	host->timeout_clks = clks;
	if (host->mmc->actual_clock == 0) {
		timeout = 0;
	} else {
		clk_ns  = 1000000000UL / host->mmc->actual_clock;
		timeout = (ns + clk_ns - 1) / clk_ns + clks;
		/* in 1048576 sclk cycle unit */
		timeout = (timeout + (0x1 << 20) - 1) >> 20;
		if (host->dev_comp->clk_div_bits == 8)
			sdr_get_field(host->base + MSDC_CFG,
				      MSDC_CFG_CKMOD, &mode);
		else
			sdr_get_field(host->base + MSDC_CFG,
				      MSDC_CFG_CKMOD_EXTRA, &mode);
		/*DDR mode will double the clk cycles for data timeout */
		timeout = mode >= 2 ? timeout * 2 : timeout;
		timeout = timeout > 1 ? timeout - 1 : 0;
		timeout = timeout > 255 ? 255 : timeout;
	}
	sdr_set_field(host->base + SDC_CFG, SDC_CFG_DTOC, timeout);
}