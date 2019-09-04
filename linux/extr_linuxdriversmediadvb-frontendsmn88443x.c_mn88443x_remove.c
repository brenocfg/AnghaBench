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
struct mn88443x_priv {int /*<<< orphan*/  client_t; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct mn88443x_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mn88443x_cmn_power_off (struct mn88443x_priv*) ; 

__attribute__((used)) static int mn88443x_remove(struct i2c_client *client)
{
	struct mn88443x_priv *chip = i2c_get_clientdata(client);

	mn88443x_cmn_power_off(chip);

	i2c_unregister_device(chip->client_t);

	return 0;
}