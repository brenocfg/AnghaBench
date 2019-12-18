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
struct stmpe {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_write_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int i2c_block_write(struct stmpe *stmpe, u8 reg, u8 length,
		const u8 *values)
{
	struct i2c_client *i2c = stmpe->client;

	return i2c_smbus_write_i2c_block_data(i2c, reg, length, values);
}