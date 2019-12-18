#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_message {int dummy; } ;
struct spi_master {int dummy; } ;
struct spi_imx_data {int /*<<< orphan*/  clk_per; int /*<<< orphan*/  clk_ipg; TYPE_1__* devtype_data; } ;
struct TYPE_2__ {int (* prepare_message ) (struct spi_imx_data*,struct spi_message*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 struct spi_imx_data* spi_master_get_devdata (struct spi_master*) ; 
 int stub1 (struct spi_imx_data*,struct spi_message*) ; 

__attribute__((used)) static int
spi_imx_prepare_message(struct spi_master *master, struct spi_message *msg)
{
	struct spi_imx_data *spi_imx = spi_master_get_devdata(master);
	int ret;

	ret = clk_enable(spi_imx->clk_per);
	if (ret)
		return ret;

	ret = clk_enable(spi_imx->clk_ipg);
	if (ret) {
		clk_disable(spi_imx->clk_per);
		return ret;
	}

	ret = spi_imx->devtype_data->prepare_message(spi_imx, msg);
	if (ret) {
		clk_disable(spi_imx->clk_ipg);
		clk_disable(spi_imx->clk_per);
	}

	return ret;
}