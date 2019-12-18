#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* spi; } ;
struct adis16480 {void* ext_clk; TYPE_3__ adis; int /*<<< orphan*/  clk_mode; TYPE_1__* chip_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ has_pps_clk_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16480_CLK_INT ; 
 int /*<<< orphan*/  ADIS16480_CLK_PPS ; 
 int /*<<< orphan*/  ADIS16480_CLK_SYNC ; 
 int ENOENT ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int adis16480_get_ext_clocks(struct adis16480 *st)
{
	st->clk_mode = ADIS16480_CLK_INT;
	st->ext_clk = devm_clk_get(&st->adis.spi->dev, "sync");
	if (!IS_ERR_OR_NULL(st->ext_clk)) {
		st->clk_mode = ADIS16480_CLK_SYNC;
		return 0;
	}

	if (PTR_ERR(st->ext_clk) != -ENOENT) {
		dev_err(&st->adis.spi->dev, "failed to get ext clk\n");
		return PTR_ERR(st->ext_clk);
	}

	if (st->chip_info->has_pps_clk_mode) {
		st->ext_clk = devm_clk_get(&st->adis.spi->dev, "pps");
		if (!IS_ERR_OR_NULL(st->ext_clk)) {
			st->clk_mode = ADIS16480_CLK_PPS;
			return 0;
		}

		if (PTR_ERR(st->ext_clk) != -ENOENT) {
			dev_err(&st->adis.spi->dev, "failed to get ext clk\n");
			return PTR_ERR(st->ext_clk);
		}
	}

	return 0;
}