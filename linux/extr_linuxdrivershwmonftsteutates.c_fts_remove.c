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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct fts_data {int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 struct fts_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts_remove(struct i2c_client *client)
{
	struct fts_data *data = dev_get_drvdata(&client->dev);

	watchdog_unregister_device(&data->wdd);
	return 0;
}