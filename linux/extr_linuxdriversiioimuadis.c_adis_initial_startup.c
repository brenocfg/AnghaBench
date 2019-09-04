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
struct TYPE_3__ {int /*<<< orphan*/  startup_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  adis_reset (struct adis*) ; 
 int adis_self_test (struct adis*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

int adis_initial_startup(struct adis *adis)
{
	int ret;

	ret = adis_self_test(adis);
	if (ret) {
		dev_err(&adis->spi->dev, "Self-test failed, trying reset.\n");
		adis_reset(adis);
		msleep(adis->data->startup_delay);
		ret = adis_self_test(adis);
		if (ret) {
			dev_err(&adis->spi->dev, "Second self-test failed, giving up.\n");
			return ret;
		}
	}

	return 0;
}