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
typedef  int /*<<< orphan*/  u8 ;
struct mma8452_data {int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  MMA8452_OUT_X ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int mma8452_drdy (struct mma8452_data*) ; 
 int mma8452_set_runtime_pm_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mma8452_read(struct mma8452_data *data, __be16 buf[3])
{
	int ret = mma8452_drdy(data);

	if (ret < 0)
		return ret;

	ret = mma8452_set_runtime_pm_state(data->client, true);
	if (ret)
		return ret;

	ret = i2c_smbus_read_i2c_block_data(data->client, MMA8452_OUT_X,
					    3 * sizeof(__be16), (u8 *)buf);

	ret = mma8452_set_runtime_pm_state(data->client, false);

	return ret;
}