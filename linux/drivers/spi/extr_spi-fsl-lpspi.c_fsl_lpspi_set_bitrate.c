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
typedef  int u8 ;
struct lpspi_config {unsigned int speed_hz; int prescale; } ;
struct fsl_lpspi_data {int /*<<< orphan*/  dev; scalar_t__ base; struct lpspi_config config; int /*<<< orphan*/  clk_per; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IMX7ULP_CCR ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned int* clkdivs ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int fsl_lpspi_set_bitrate(struct fsl_lpspi_data *fsl_lpspi)
{
	struct lpspi_config config = fsl_lpspi->config;
	unsigned int perclk_rate, scldiv;
	u8 prescale;

	perclk_rate = clk_get_rate(fsl_lpspi->clk_per);

	if (config.speed_hz > perclk_rate / 2) {
		dev_err(fsl_lpspi->dev,
		      "per-clk should be at least two times of transfer speed");
		return -EINVAL;
	}

	for (prescale = 0; prescale < 8; prescale++) {
		scldiv = perclk_rate /
			 (clkdivs[prescale] * config.speed_hz) - 2;
		if (scldiv < 256) {
			fsl_lpspi->config.prescale = prescale;
			break;
		}
	}

	if (prescale == 8 && scldiv >= 256)
		return -EINVAL;

	writel(scldiv | (scldiv << 8) | ((scldiv >> 1) << 16),
					fsl_lpspi->base + IMX7ULP_CCR);

	dev_dbg(fsl_lpspi->dev, "perclk=%d, speed=%d, prescale=%d, scldiv=%d\n",
		perclk_rate, config.speed_hz, prescale, scldiv);

	return 0;
}