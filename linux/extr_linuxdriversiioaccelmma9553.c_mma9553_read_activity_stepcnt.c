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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mma9553_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMA9551_APPID_PEDOMETER ; 
 int /*<<< orphan*/  MMA9553_MASK_STATUS_ACTIVITY ; 
 int /*<<< orphan*/  MMA9553_REG_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int mma9551_read_status_words (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mma9553_get_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mma9553_read_activity_stepcnt(struct mma9553_data *data,
					 u8 *activity, u16 *stepcnt)
{
	u16 buf[2];
	int ret;

	ret = mma9551_read_status_words(data->client, MMA9551_APPID_PEDOMETER,
					MMA9553_REG_STATUS, ARRAY_SIZE(buf),
					buf);
	if (ret < 0) {
		dev_err(&data->client->dev,
			"error reading status and stepcnt\n");
		return ret;
	}

	*activity = mma9553_get_bits(buf[0], MMA9553_MASK_STATUS_ACTIVITY);
	*stepcnt = buf[1];

	return 0;
}