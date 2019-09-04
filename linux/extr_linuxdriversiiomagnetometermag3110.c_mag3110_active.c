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
struct mag3110_data {int /*<<< orphan*/  ctrl_reg1; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAG3110_CTRL_REG1 ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mag3110_active(struct mag3110_data *data)
{
	return i2c_smbus_write_byte_data(data->client, MAG3110_CTRL_REG1,
					 data->ctrl_reg1);
}