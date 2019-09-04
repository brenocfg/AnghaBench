#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct twl_client {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int ready; struct twl_client* twl_modules; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int twl4030_exit_irq () ; 
 int twl6030_exit_irq () ; 
 scalar_t__ twl_class_is_4030 () ; 
 unsigned int twl_get_num_slaves () ; 
 TYPE_1__* twl_priv ; 

__attribute__((used)) static int twl_remove(struct i2c_client *client)
{
	unsigned i, num_slaves;
	int status;

	if (twl_class_is_4030())
		status = twl4030_exit_irq();
	else
		status = twl6030_exit_irq();

	if (status < 0)
		return status;

	num_slaves = twl_get_num_slaves();
	for (i = 0; i < num_slaves; i++) {
		struct twl_client	*twl = &twl_priv->twl_modules[i];

		if (twl->client && twl->client != client)
			i2c_unregister_device(twl->client);
		twl->client = NULL;
	}
	twl_priv->ready = false;
	return 0;
}