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
typedef  int u32 ;
struct axxia_i2c_dev {int bus_clk_rate; scalar_t__ base; int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c_clk; } ;

/* Variables and functions */
 scalar_t__ GLOBAL_CONTROL ; 
 scalar_t__ INTERRUPT_ENABLE ; 
 scalar_t__ SCL_HIGH_PERIOD ; 
 scalar_t__ SCL_LOW_PERIOD ; 
 int SCL_WAIT_TIMEOUT_NS ; 
 scalar_t__ SDA_HOLD_TIME ; 
 scalar_t__ SDA_SETUP_TIME ; 
 scalar_t__ SOFT_RESET ; 
 scalar_t__ SPIKE_FLTR_LEN ; 
 scalar_t__ TIMER_CLOCK_DIV ; 
 scalar_t__ WAIT_TIMER_CONTROL ; 
 int WT_EN ; 
 int WT_VALUE (int) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i2c_int_disable (struct axxia_i2c_dev*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int ns_to_clk (int,int) ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int axxia_i2c_init(struct axxia_i2c_dev *idev)
{
	u32 divisor = clk_get_rate(idev->i2c_clk) / idev->bus_clk_rate;
	u32 clk_mhz = clk_get_rate(idev->i2c_clk) / 1000000;
	u32 t_setup;
	u32 t_high, t_low;
	u32 tmo_clk;
	u32 prescale;
	unsigned long timeout;

	dev_dbg(idev->dev, "rate=%uHz per_clk=%uMHz -> ratio=1:%u\n",
		idev->bus_clk_rate, clk_mhz, divisor);

	/* Reset controller */
	writel(0x01, idev->base + SOFT_RESET);
	timeout = jiffies + msecs_to_jiffies(100);
	while (readl(idev->base + SOFT_RESET) & 1) {
		if (time_after(jiffies, timeout)) {
			dev_warn(idev->dev, "Soft reset failed\n");
			break;
		}
	}

	/* Enable Master Mode */
	writel(0x1, idev->base + GLOBAL_CONTROL);

	if (idev->bus_clk_rate <= 100000) {
		/* Standard mode SCL 50/50, tSU:DAT = 250 ns */
		t_high = divisor * 1 / 2;
		t_low = divisor * 1 / 2;
		t_setup = ns_to_clk(250, clk_mhz);
	} else {
		/* Fast mode SCL 33/66, tSU:DAT = 100 ns */
		t_high = divisor * 1 / 3;
		t_low = divisor * 2 / 3;
		t_setup = ns_to_clk(100, clk_mhz);
	}

	/* SCL High Time */
	writel(t_high, idev->base + SCL_HIGH_PERIOD);
	/* SCL Low Time */
	writel(t_low, idev->base + SCL_LOW_PERIOD);
	/* SDA Setup Time */
	writel(t_setup, idev->base + SDA_SETUP_TIME);
	/* SDA Hold Time, 300ns */
	writel(ns_to_clk(300, clk_mhz), idev->base + SDA_HOLD_TIME);
	/* Filter <50ns spikes */
	writel(ns_to_clk(50, clk_mhz), idev->base + SPIKE_FLTR_LEN);

	/* Configure Time-Out Registers */
	tmo_clk = ns_to_clk(SCL_WAIT_TIMEOUT_NS, clk_mhz);

	/* Find prescaler value that makes tmo_clk fit in 15-bits counter. */
	for (prescale = 0; prescale < 15; ++prescale) {
		if (tmo_clk <= 0x7fff)
			break;
		tmo_clk >>= 1;
	}
	if (tmo_clk > 0x7fff)
		tmo_clk = 0x7fff;

	/* Prescale divider (log2) */
	writel(prescale, idev->base + TIMER_CLOCK_DIV);
	/* Timeout in divided clocks */
	writel(WT_EN | WT_VALUE(tmo_clk), idev->base + WAIT_TIMER_CONTROL);

	/* Mask all master interrupt bits */
	i2c_int_disable(idev, ~0);

	/* Interrupt enable */
	writel(0x01, idev->base + INTERRUPT_ENABLE);

	return 0;
}