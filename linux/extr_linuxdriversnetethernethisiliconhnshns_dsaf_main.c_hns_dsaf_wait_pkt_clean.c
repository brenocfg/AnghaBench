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
typedef  scalar_t__ u32 ;
struct dsaf_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DSAF_SERVICE_NW_NUM ; 
 scalar_t__ DSAF_VOQ_IN_PKT_NUM_0_REG ; 
 scalar_t__ DSAF_VOQ_OUT_PKT_NUM_0_REG ; 
 int DSAF_XGE_NUM ; 
 int EBUSY ; 
 int HNS_MAX_WAIT_CNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ dsaf_read_dev (struct dsaf_device*,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int hns_dsaf_wait_pkt_clean(struct dsaf_device *dsaf_dev, int port)
{
	u32 val, val_tmp;
	int wait_cnt;

	if (port >= DSAF_SERVICE_NW_NUM)
		return 0;

	wait_cnt = 0;
	while (wait_cnt++ < HNS_MAX_WAIT_CNT) {
		val = dsaf_read_dev(dsaf_dev, DSAF_VOQ_IN_PKT_NUM_0_REG +
			(port + DSAF_XGE_NUM) * 0x40);
		val_tmp = dsaf_read_dev(dsaf_dev, DSAF_VOQ_OUT_PKT_NUM_0_REG +
			(port + DSAF_XGE_NUM) * 0x40);
		if (val == val_tmp)
			break;

		usleep_range(100, 200);
	}

	if (wait_cnt >= HNS_MAX_WAIT_CNT) {
		dev_err(dsaf_dev->dev, "hns dsaf clean wait timeout(%u - %u).\n",
			val, val_tmp);
		return -EBUSY;
	}

	return 0;
}