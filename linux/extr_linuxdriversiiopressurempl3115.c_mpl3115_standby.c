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
struct mpl3115_data {int ctrl_reg1; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int MPL3115_CTRL_ACTIVE ; 
 int /*<<< orphan*/  MPL3115_CTRL_REG1 ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mpl3115_standby(struct mpl3115_data *data)
{
	return i2c_smbus_write_byte_data(data->client, MPL3115_CTRL_REG1,
		data->ctrl_reg1 & ~MPL3115_CTRL_ACTIVE);
}