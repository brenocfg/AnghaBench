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
struct max30100_data {int /*<<< orphan*/  buffer; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX30100_REG_FIFO_DATA ; 
 int MAX30100_REG_FIFO_DATA_ENTRY_LEN ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max30100_read_measurement(struct max30100_data *data)
{
	int ret;

	ret = i2c_smbus_read_i2c_block_data(data->client,
					    MAX30100_REG_FIFO_DATA,
					    MAX30100_REG_FIFO_DATA_ENTRY_LEN,
					    (u8 *) &data->buffer);

	return (ret == MAX30100_REG_FIFO_DATA_ENTRY_LEN) ? 0 : ret;
}