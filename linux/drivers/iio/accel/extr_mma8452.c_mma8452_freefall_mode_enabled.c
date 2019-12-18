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
 int /*<<< orphan*/  MMA8452_FF_MT_CFG ; 
 int MMA8452_FF_MT_CFG_OAE ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mma8452_freefall_mode_enabled(struct mma8452_data *data)
{
	int val;

	val = i2c_smbus_read_byte_data(data->client, MMA8452_FF_MT_CFG);
	if (val < 0)
		return val;

	return !(val & MMA8452_FF_MT_CFG_OAE);
}