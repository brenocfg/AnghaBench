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
struct sun6i_spi {int /*<<< orphan*/  hclk; int /*<<< orphan*/  mclk; int /*<<< orphan*/  rstc; } ;
struct spi_master {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int SUN6I_GBL_CTL_BUS_ENABLE ; 
 int SUN6I_GBL_CTL_MASTER ; 
 int /*<<< orphan*/  SUN6I_GBL_CTL_REG ; 
 int SUN6I_GBL_CTL_TP ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct spi_master* dev_get_drvdata (struct device*) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 struct sun6i_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  sun6i_spi_write (struct sun6i_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun6i_spi_runtime_resume(struct device *dev)
{
	struct spi_master *master = dev_get_drvdata(dev);
	struct sun6i_spi *sspi = spi_master_get_devdata(master);
	int ret;

	ret = clk_prepare_enable(sspi->hclk);
	if (ret) {
		dev_err(dev, "Couldn't enable AHB clock\n");
		goto out;
	}

	ret = clk_prepare_enable(sspi->mclk);
	if (ret) {
		dev_err(dev, "Couldn't enable module clock\n");
		goto err;
	}

	ret = reset_control_deassert(sspi->rstc);
	if (ret) {
		dev_err(dev, "Couldn't deassert the device from reset\n");
		goto err2;
	}

	sun6i_spi_write(sspi, SUN6I_GBL_CTL_REG,
			SUN6I_GBL_CTL_BUS_ENABLE | SUN6I_GBL_CTL_MASTER | SUN6I_GBL_CTL_TP);

	return 0;

err2:
	clk_disable_unprepare(sspi->mclk);
err:
	clk_disable_unprepare(sspi->hclk);
out:
	return ret;
}