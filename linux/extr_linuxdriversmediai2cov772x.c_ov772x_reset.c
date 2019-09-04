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
 int /*<<< orphan*/  COM2 ; 
 int /*<<< orphan*/  COM7 ; 
 int /*<<< orphan*/  SCCB_RESET ; 
 int /*<<< orphan*/  SOFT_SLEEP_MODE ; 
 int ov772x_mask_set (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ov772x_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ov772x_reset(struct i2c_client *client)
{
	int ret;

	ret = ov772x_write(client, COM7, SCCB_RESET);
	if (ret < 0)
		return ret;

	usleep_range(1000, 5000);

	return ov772x_mask_set(client, COM2, SOFT_SLEEP_MODE, SOFT_SLEEP_MODE);
}