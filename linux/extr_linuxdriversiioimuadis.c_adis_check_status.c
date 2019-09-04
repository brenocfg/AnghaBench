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
typedef  int uint16_t ;
struct adis {TYPE_2__* data; TYPE_1__* spi; } ;
struct TYPE_4__ {int status_error_mask; int /*<<< orphan*/ * status_error_msgs; int /*<<< orphan*/  diag_stat_reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EIO ; 
 int adis_read_reg_16 (struct adis*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int adis_check_status(struct adis *adis)
{
	uint16_t status;
	int ret;
	int i;

	ret = adis_read_reg_16(adis, adis->data->diag_stat_reg, &status);
	if (ret < 0)
		return ret;

	status &= adis->data->status_error_mask;

	if (status == 0)
		return 0;

	for (i = 0; i < 16; ++i) {
		if (status & BIT(i)) {
			dev_err(&adis->spi->dev, "%s.\n",
				adis->data->status_error_msgs[i]);
		}
	}

	return -EIO;
}