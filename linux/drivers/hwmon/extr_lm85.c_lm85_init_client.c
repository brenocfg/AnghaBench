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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM85_REG_CONFIG ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int lm85_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm85_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lm85_init_client(struct i2c_client *client)
{
	int value;

	/* Start monitoring if needed */
	value = lm85_read_value(client, LM85_REG_CONFIG);
	if (!(value & 0x01)) {
		dev_info(&client->dev, "Starting monitoring\n");
		lm85_write_value(client, LM85_REG_CONFIG, value | 0x01);
	}

	/* Warn about unusual configuration bits */
	if (value & 0x02)
		dev_warn(&client->dev, "Device configuration is locked\n");
	if (!(value & 0x04))
		dev_warn(&client->dev, "Device is not ready\n");
}