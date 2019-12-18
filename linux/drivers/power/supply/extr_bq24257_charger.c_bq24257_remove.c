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
struct bq24257_device {int /*<<< orphan*/  iilimit_setup_work; scalar_t__ iilimit_autoset_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_RESET ; 
 int /*<<< orphan*/  bq24257_field_write (struct bq24257_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct bq24257_device* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int bq24257_remove(struct i2c_client *client)
{
	struct bq24257_device *bq = i2c_get_clientdata(client);

	if (bq->iilimit_autoset_enable)
		cancel_delayed_work_sync(&bq->iilimit_setup_work);

	bq24257_field_write(bq, F_RESET, 1); /* reset to defaults */

	return 0;
}