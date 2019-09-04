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
struct cma3000_accl_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cma3000_exit (struct cma3000_accl_data*) ; 
 struct cma3000_accl_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int cma3000_i2c_remove(struct i2c_client *client)
{
	struct cma3000_accl_data *data = i2c_get_clientdata(client);

	cma3000_exit(data);

	return 0;
}