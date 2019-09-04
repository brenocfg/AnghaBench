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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int I2C_SMBUS_BLOCK_MAX ; 
 int i2c_smbus_read_block_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pem_read_block(struct i2c_client *client, u8 command, u8 *data,
			  int data_len)
{
	u8 block_buffer[I2C_SMBUS_BLOCK_MAX];
	int result;

	result = i2c_smbus_read_block_data(client, command, block_buffer);
	if (unlikely(result < 0))
		goto abort;
	if (unlikely(result == 0xff || result != data_len)) {
		result = -EIO;
		goto abort;
	}
	memcpy(data, block_buffer, data_len);
	result = 0;
abort:
	return result;
}