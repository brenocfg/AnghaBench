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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ad714x_chip {void** xfer_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* cpu_to_be16 (unsigned short) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ad714x_i2c_write(struct ad714x_chip *chip,
			    unsigned short reg, unsigned short data)
{
	struct i2c_client *client = to_i2c_client(chip->dev);
	int error;

	chip->xfer_buf[0] = cpu_to_be16(reg);
	chip->xfer_buf[1] = cpu_to_be16(data);

	error = i2c_master_send(client, (u8 *)chip->xfer_buf,
				2 * sizeof(*chip->xfer_buf));
	if (unlikely(error < 0)) {
		dev_err(&client->dev, "I2C write error: %d\n", error);
		return error;
	}

	return 0;
}