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
struct lm90_data {int /*<<< orphan*/  config_orig; int /*<<< orphan*/  convrate_orig; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM90_REG_W_CONFIG1 ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm90_write_convrate (struct lm90_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lm90_restore_conf(void *_data)
{
	struct lm90_data *data = _data;
	struct i2c_client *client = data->client;

	/* Restore initial configuration */
	lm90_write_convrate(data, data->convrate_orig);
	i2c_smbus_write_byte_data(client, LM90_REG_W_CONFIG1,
				  data->config_orig);
}