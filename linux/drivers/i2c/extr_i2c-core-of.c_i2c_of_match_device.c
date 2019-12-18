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
struct of_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct of_device_id const* i2c_of_match_device_sysfs (struct of_device_id const*,struct i2c_client*) ; 
 struct of_device_id* of_match_device (struct of_device_id const*,int /*<<< orphan*/ *) ; 

const struct of_device_id
*i2c_of_match_device(const struct of_device_id *matches,
		     struct i2c_client *client)
{
	const struct of_device_id *match;

	if (!(client && matches))
		return NULL;

	match = of_match_device(matches, &client->dev);
	if (match)
		return match;

	return i2c_of_match_device_sysfs(matches, client);
}