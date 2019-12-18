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
struct pismo_data {int /*<<< orphan*/ * dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 struct pismo_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct pismo_data*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pismo_remove(struct i2c_client *client)
{
	struct pismo_data *pismo = i2c_get_clientdata(client);
	int i;

	for (i = 0; i < ARRAY_SIZE(pismo->dev); i++)
		platform_device_unregister(pismo->dev[i]);

	kfree(pismo);

	return 0;
}