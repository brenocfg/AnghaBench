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
 int /*<<< orphan*/  LM77_REG_CONF ; 
 int lm77_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm77_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lm77_init_client(struct i2c_client *client)
{
	/* Initialize the LM77 chip - turn off shutdown mode */
	int conf = lm77_read_value(client, LM77_REG_CONF);
	if (conf & 1)
		lm77_write_value(client, LM77_REG_CONF, conf & 0xfe);
}