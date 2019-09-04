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
 int /*<<< orphan*/  W83793_REG_CONFIG ; 
 scalar_t__ reset ; 
 int w83793_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83793_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void w83793_init_client(struct i2c_client *client)
{
	if (reset)
		w83793_write_value(client, W83793_REG_CONFIG, 0x80);

	/* Start monitoring */
	w83793_write_value(client, W83793_REG_CONFIG,
			   w83793_read_value(client, W83793_REG_CONFIG) | 0x01);
}