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
struct driver_data {int ssp_type; TYPE_2__* controller; } ;
struct chip_data {int /*<<< orphan*/  dds_rate; } ;
struct TYPE_4__ {TYPE_1__* cur_msg; } ;
struct TYPE_3__ {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
#define  QUARK_X1000_SSP 128 
 unsigned int quark_x1000_get_clk_div (int,int /*<<< orphan*/ *) ; 
 struct chip_data* spi_get_ctldata (int /*<<< orphan*/ ) ; 
 unsigned int ssp_get_clk_div (struct driver_data*,int) ; 

__attribute__((used)) static unsigned int pxa2xx_ssp_get_clk_div(struct driver_data *drv_data,
					   int rate)
{
	struct chip_data *chip =
		spi_get_ctldata(drv_data->controller->cur_msg->spi);
	unsigned int clk_div;

	switch (drv_data->ssp_type) {
	case QUARK_X1000_SSP:
		clk_div = quark_x1000_get_clk_div(rate, &chip->dds_rate);
		break;
	default:
		clk_div = ssp_get_clk_div(drv_data, rate);
		break;
	}
	return clk_div << 8;
}