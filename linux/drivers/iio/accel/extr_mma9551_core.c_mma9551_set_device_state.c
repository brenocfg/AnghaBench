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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMA9551_APPID_SLEEP_WAKE ; 
 int /*<<< orphan*/  MMA9551_SLEEP_CFG ; 
 int MMA9551_SLEEP_CFG_FLEEN ; 
 int MMA9551_SLEEP_CFG_SCHEN ; 
 int MMA9551_SLEEP_CFG_SNCEN ; 
 int mma9551_update_config_bits (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int mma9551_set_device_state(struct i2c_client *client, bool enable)
{
	return mma9551_update_config_bits(client, MMA9551_APPID_SLEEP_WAKE,
					  MMA9551_SLEEP_CFG,
					  MMA9551_SLEEP_CFG_SNCEN |
					  MMA9551_SLEEP_CFG_FLEEN |
					  MMA9551_SLEEP_CFG_SCHEN,
					  enable ? MMA9551_SLEEP_CFG_SCHEN |
					  MMA9551_SLEEP_CFG_FLEEN :
					  MMA9551_SLEEP_CFG_SNCEN);
}