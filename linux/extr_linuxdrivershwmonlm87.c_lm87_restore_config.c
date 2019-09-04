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
struct lm87_data {int /*<<< orphan*/  config; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM87_REG_CONFIG ; 
 struct lm87_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  lm87_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lm87_restore_config(void *arg)
{
	struct i2c_client *client = arg;
	struct lm87_data *data = i2c_get_clientdata(client);

	lm87_write_value(client, LM87_REG_CONFIG, data->config);
}