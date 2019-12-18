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
typedef  int /*<<< orphan*/  u32 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMA9551_APPID_RSC ; 
 scalar_t__ MMA9551_RSC_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ MMA9551_RSC_RESET ; 
 int /*<<< orphan*/  MMA9551_RSC_VAL (int /*<<< orphan*/ ) ; 
 int mma9551_write_config_byte (struct i2c_client*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

int mma9551_app_reset(struct i2c_client *client, u32 app_mask)
{
	return mma9551_write_config_byte(client, MMA9551_APPID_RSC,
					 MMA9551_RSC_RESET +
					 MMA9551_RSC_OFFSET(app_mask),
					 MMA9551_RSC_VAL(app_mask));
}