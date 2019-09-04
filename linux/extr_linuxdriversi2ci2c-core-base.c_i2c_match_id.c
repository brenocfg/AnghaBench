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
struct i2c_device_id {scalar_t__* name; } ;
struct i2c_client {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__*) ; 

const struct i2c_device_id *i2c_match_id(const struct i2c_device_id *id,
						const struct i2c_client *client)
{
	if (!(id && client))
		return NULL;

	while (id->name[0]) {
		if (strcmp(client->name, id->name) == 0)
			return id;
		id++;
	}
	return NULL;
}