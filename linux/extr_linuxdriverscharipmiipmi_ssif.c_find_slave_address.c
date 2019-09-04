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

__attribute__((used)) static int find_slave_address(struct i2c_client *client, int slave_addr)
{
#ifdef CONFIG_IPMI_DMI_DECODE
	if (!slave_addr)
		slave_addr = ipmi_dmi_get_slave_addr(
			SI_TYPE_INVALID,
			i2c_adapter_id(client->adapter),
			client->addr);
#endif

	return slave_addr;
}