#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* spi; } ;
struct ad7124_state {TYPE_2__ sd; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7124_STATUS ; 
 unsigned int AD7124_STATUS_POR_FLAG_MSK ; 
 int EIO ; 
 int ad_sd_read_reg (TYPE_2__*,int /*<<< orphan*/ ,int,unsigned int*) ; 
 int ad_sd_reset (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ad7124_soft_reset(struct ad7124_state *st)
{
	unsigned int readval, timeout;
	int ret;

	ret = ad_sd_reset(&st->sd, 64);
	if (ret < 0)
		return ret;

	timeout = 100;
	do {
		ret = ad_sd_read_reg(&st->sd, AD7124_STATUS, 1, &readval);
		if (ret < 0)
			return ret;

		if (!(readval & AD7124_STATUS_POR_FLAG_MSK))
			return 0;

		/* The AD7124 requires typically 2ms to power up and settle */
		usleep_range(100, 2000);
	} while (--timeout);

	dev_err(&st->sd.spi->dev, "Soft reset failed\n");

	return -EIO;
}