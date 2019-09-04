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
struct smm665_data {int /*<<< orphan*/  cmdreg; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct smm665_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smm665_remove(struct i2c_client *client)
{
	struct smm665_data *data = i2c_get_clientdata(client);

	i2c_unregister_device(data->cmdreg);
	return 0;
}