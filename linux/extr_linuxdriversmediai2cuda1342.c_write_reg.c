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
 int /*<<< orphan*/  i2c_smbus_write_word_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swab16 (int) ; 

__attribute__((used)) static int write_reg(struct i2c_client *client, int reg, int value)
{
	/* UDA1342 wants MSB first, but SMBus sends LSB first */
	i2c_smbus_write_word_data(client, reg, swab16(value));
	return 0;
}