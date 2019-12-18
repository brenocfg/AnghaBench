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
 int /*<<< orphan*/  mt9t112_reg_mask_set (int,struct i2c_client const*,int,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mt9t112_reset(const struct i2c_client *client)
{
	int ret;

	mt9t112_reg_mask_set(ret, client, 0x001a, 0x0001, 0x0001);
	usleep_range(1000, 5000);
	mt9t112_reg_mask_set(ret, client, 0x001a, 0x0001, 0x0000);

	return ret;
}