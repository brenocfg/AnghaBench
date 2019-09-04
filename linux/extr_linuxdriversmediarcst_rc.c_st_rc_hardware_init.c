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
struct st_rc_device {int overclocking; int sample_mult; int sample_div; scalar_t__ rx_base; scalar_t__ base; int /*<<< orphan*/  sys_clock; int /*<<< orphan*/  rstc; } ;

/* Variables and functions */
 scalar_t__ IRB_MAX_SYM_PERIOD ; 
 scalar_t__ IRB_RX_POLARITY_INV ; 
 int IRB_SAMPLE_FREQ ; 
 scalar_t__ IRB_SAMPLE_RATE_COMM ; 
 unsigned int MAX_SYMB_TIME ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void st_rc_hardware_init(struct st_rc_device *dev)
{
	int baseclock, freqdiff;
	unsigned int rx_max_symbol_per = MAX_SYMB_TIME;
	unsigned int rx_sampling_freq_div;

	/* Enable the IP */
	reset_control_deassert(dev->rstc);

	clk_prepare_enable(dev->sys_clock);
	baseclock = clk_get_rate(dev->sys_clock);

	/* IRB input pins are inverted internally from high to low. */
	writel(1, dev->rx_base + IRB_RX_POLARITY_INV);

	rx_sampling_freq_div = baseclock / IRB_SAMPLE_FREQ;
	writel(rx_sampling_freq_div, dev->base + IRB_SAMPLE_RATE_COMM);

	freqdiff = baseclock - (rx_sampling_freq_div * IRB_SAMPLE_FREQ);
	if (freqdiff) { /* over clocking, workout the adjustment factors */
		dev->overclocking = true;
		dev->sample_mult = 1000;
		dev->sample_div = baseclock / (10000 * rx_sampling_freq_div);
		rx_max_symbol_per = (rx_max_symbol_per * 1000)/dev->sample_div;
	}

	writel(rx_max_symbol_per, dev->rx_base + IRB_MAX_SYM_PERIOD);
}