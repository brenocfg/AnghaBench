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
struct geni_se {int /*<<< orphan*/  clk; } ;
struct spi_geni_master {unsigned int oversampling; int /*<<< orphan*/  dev; struct geni_se se; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned long,unsigned int) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned long,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int geni_se_clk_freq_match (struct geni_se*,unsigned int,unsigned int*,unsigned long*,int) ; 

__attribute__((used)) static int get_spi_clk_cfg(unsigned int speed_hz,
			struct spi_geni_master *mas,
			unsigned int *clk_idx,
			unsigned int *clk_div)
{
	unsigned long sclk_freq;
	unsigned int actual_hz;
	struct geni_se *se = &mas->se;
	int ret;

	ret = geni_se_clk_freq_match(&mas->se,
				speed_hz * mas->oversampling,
				clk_idx, &sclk_freq, false);
	if (ret) {
		dev_err(mas->dev, "Failed(%d) to find src clk for %dHz\n",
							ret, speed_hz);
		return ret;
	}

	*clk_div = DIV_ROUND_UP(sclk_freq, mas->oversampling * speed_hz);
	actual_hz = sclk_freq / (mas->oversampling * *clk_div);

	dev_dbg(mas->dev, "req %u=>%u sclk %lu, idx %d, div %d\n", speed_hz,
				actual_hz, sclk_freq, *clk_idx, *clk_div);
	ret = clk_set_rate(se->clk, sclk_freq);
	if (ret)
		dev_err(mas->dev, "clk_set_rate failed %d\n", ret);
	return ret;
}