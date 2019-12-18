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
typedef  int /*<<< orphan*/  u8 ;
struct lm93_data {int /*<<< orphan*/  block10; int /*<<< orphan*/  block1; scalar_t__ block9; scalar_t__ block8; scalar_t__ block5; scalar_t__ block4; scalar_t__ block2; scalar_t__ block7; scalar_t__ block3; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lm93_read_block (struct i2c_client*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lm93_update_client_common (struct lm93_data*,struct i2c_client*) ; 

__attribute__((used)) static void lm93_update_client_full(struct lm93_data *data,
				    struct i2c_client *client)
{
	dev_dbg(&client->dev, "starting device update (block data enabled)\n");

	/* in1 - in16: values & limits */
	lm93_read_block(client, 3, (u8 *)(data->block3));
	lm93_read_block(client, 7, (u8 *)(data->block7));

	/* temp1 - temp4: values */
	lm93_read_block(client, 2, (u8 *)(data->block2));

	/* prochot1 - prochot2: values */
	lm93_read_block(client, 4, (u8 *)(data->block4));

	/* fan1 - fan4: values & limits */
	lm93_read_block(client, 5, (u8 *)(data->block5));
	lm93_read_block(client, 8, (u8 *)(data->block8));

	/* pmw control registers */
	lm93_read_block(client, 9, (u8 *)(data->block9));

	/* alarm values */
	lm93_read_block(client, 1, (u8 *)(&data->block1));

	/* auto/pwm registers */
	lm93_read_block(client, 10, (u8 *)(&data->block10));

	lm93_update_client_common(data, client);
}