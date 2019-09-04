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
struct mma8452_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int MMA8452_CTRL_ACTIVE ; 
 int /*<<< orphan*/  MMA8452_CTRL_REG1 ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mma8452_is_active(struct mma8452_data *data)
{
	int reg;

	reg = i2c_smbus_read_byte_data(data->client, MMA8452_CTRL_REG1);
	if (reg < 0)
		return reg;

	return reg & MMA8452_CTRL_ACTIVE;
}