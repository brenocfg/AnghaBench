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
struct adis {TYPE_2__* data; TYPE_1__* spi; } ;
struct TYPE_4__ {int self_test_mask; int /*<<< orphan*/  msc_ctrl_reg; scalar_t__ self_test_no_autoclear; int /*<<< orphan*/  startup_delay; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int adis_check_status (struct adis*) ; 
 int adis_write_reg_16 (struct adis*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adis_self_test(struct adis *adis)
{
	int ret;

	ret = adis_write_reg_16(adis, adis->data->msc_ctrl_reg,
			adis->data->self_test_mask);
	if (ret) {
		dev_err(&adis->spi->dev, "Failed to initiate self test: %d\n",
			ret);
		return ret;
	}

	msleep(adis->data->startup_delay);

	ret = adis_check_status(adis);

	if (adis->data->self_test_no_autoclear)
		adis_write_reg_16(adis, adis->data->msc_ctrl_reg, 0x00);

	return ret;
}