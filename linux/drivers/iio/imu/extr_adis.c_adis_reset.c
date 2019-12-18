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
struct adis {TYPE_2__* spi; TYPE_1__* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  glob_cmd_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS_GLOB_CMD_SW_RESET ; 
 int adis_write_reg_8 (struct adis*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 

int adis_reset(struct adis *adis)
{
	int ret;

	ret = adis_write_reg_8(adis, adis->data->glob_cmd_reg,
			ADIS_GLOB_CMD_SW_RESET);
	if (ret)
		dev_err(&adis->spi->dev, "Failed to reset device: %d\n", ret);

	return ret;
}