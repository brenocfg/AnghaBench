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
struct sbs_info {int /*<<< orphan*/  work; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct sbs_info* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int sbs_remove(struct i2c_client *client)
{
	struct sbs_info *chip = i2c_get_clientdata(client);

	cancel_delayed_work_sync(&chip->work);

	return 0;
}