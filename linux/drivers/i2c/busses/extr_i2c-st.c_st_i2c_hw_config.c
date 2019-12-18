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
struct st_i2c_timings {int rate; int rep_start_hold; int rep_start_setup; int start_hold; int data_setup_time; int stop_setup_time; int bus_free_time; } ;
struct st_i2c_dev {size_t mode; unsigned long scl_min_width_us; unsigned long sda_min_width_us; scalar_t__ base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ SSC_BRG ; 
 scalar_t__ SSC_BUS_FREE ; 
 scalar_t__ SSC_CLR ; 
 int SSC_CLR_NACK ; 
 int SSC_CLR_REPSTRT ; 
 int SSC_CLR_SSCAAS ; 
 int SSC_CLR_SSCARBL ; 
 int SSC_CLR_SSCSTOP ; 
 scalar_t__ SSC_CTL ; 
 int SSC_CTL_DATA_WIDTH_9 ; 
 int SSC_CTL_HB ; 
 int SSC_CTL_PH ; 
 int SSC_CTL_PO ; 
 scalar_t__ SSC_DATA_SETUP ; 
 scalar_t__ SSC_I2C ; 
 int SSC_I2C_I2CM ; 
 scalar_t__ SSC_NOISE_SUPP_WIDTH ; 
 scalar_t__ SSC_NOISE_SUPP_WIDTH_DATAOUT ; 
 scalar_t__ SSC_PRE_SCALER_BRG ; 
 scalar_t__ SSC_PRSCALER ; 
 scalar_t__ SSC_PRSCALER_DATAOUT ; 
 scalar_t__ SSC_REP_START_HOLD ; 
 scalar_t__ SSC_REP_START_SETUP ; 
 scalar_t__ SSC_START_HOLD ; 
 scalar_t__ SSC_STOP_SETUP ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 struct st_i2c_timings* i2c_timings ; 
 int /*<<< orphan*/  st_i2c_soft_reset (struct st_i2c_dev*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void st_i2c_hw_config(struct st_i2c_dev *i2c_dev)
{
	unsigned long rate;
	u32 val, ns_per_clk;
	struct st_i2c_timings *t = &i2c_timings[i2c_dev->mode];

	st_i2c_soft_reset(i2c_dev);

	val = SSC_CLR_REPSTRT | SSC_CLR_NACK | SSC_CLR_SSCARBL |
		SSC_CLR_SSCAAS | SSC_CLR_SSCSTOP;
	writel_relaxed(val, i2c_dev->base + SSC_CLR);

	/* SSC Control register setup */
	val = SSC_CTL_PO | SSC_CTL_PH | SSC_CTL_HB | SSC_CTL_DATA_WIDTH_9;
	writel_relaxed(val, i2c_dev->base + SSC_CTL);

	rate = clk_get_rate(i2c_dev->clk);
	ns_per_clk = 1000000000 / rate;

	/* Baudrate */
	val = rate / (2 * t->rate);
	writel_relaxed(val, i2c_dev->base + SSC_BRG);

	/* Pre-scaler baudrate */
	writel_relaxed(1, i2c_dev->base + SSC_PRE_SCALER_BRG);

	/* Enable I2C mode */
	writel_relaxed(SSC_I2C_I2CM, i2c_dev->base + SSC_I2C);

	/* Repeated start hold time */
	val = t->rep_start_hold / ns_per_clk;
	writel_relaxed(val, i2c_dev->base + SSC_REP_START_HOLD);

	/* Repeated start set up time */
	val = t->rep_start_setup / ns_per_clk;
	writel_relaxed(val, i2c_dev->base + SSC_REP_START_SETUP);

	/* Start hold time */
	val = t->start_hold / ns_per_clk;
	writel_relaxed(val, i2c_dev->base + SSC_START_HOLD);

	/* Data set up time */
	val = t->data_setup_time / ns_per_clk;
	writel_relaxed(val, i2c_dev->base + SSC_DATA_SETUP);

	/* Stop set up time */
	val = t->stop_setup_time / ns_per_clk;
	writel_relaxed(val, i2c_dev->base + SSC_STOP_SETUP);

	/* Bus free time */
	val = t->bus_free_time / ns_per_clk;
	writel_relaxed(val, i2c_dev->base + SSC_BUS_FREE);

	/* Prescalers set up */
	val = rate / 10000000;
	writel_relaxed(val, i2c_dev->base + SSC_PRSCALER);
	writel_relaxed(val, i2c_dev->base + SSC_PRSCALER_DATAOUT);

	/* Noise suppression witdh */
	val = i2c_dev->scl_min_width_us * rate / 100000000;
	writel_relaxed(val, i2c_dev->base + SSC_NOISE_SUPP_WIDTH);

	/* Noise suppression max output data delay width */
	val = i2c_dev->sda_min_width_us * rate / 100000000;
	writel_relaxed(val, i2c_dev->base + SSC_NOISE_SUPP_WIDTH_DATAOUT);
}